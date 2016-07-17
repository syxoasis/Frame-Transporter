#include "../_ft_internal.h"

///

static void frame_pool_heartbeat_callback(struct ft_context * context, void * data);

//

bool frame_pool_init(struct frame_pool * this, struct ft_context * context)
{
	assert(this != NULL);
	this->zones = NULL;
	
	this->alloc_fnct = ft_pool_alloc_default;


	if (context != NULL)
	{
		ft_context_at_heartbeat(context, frame_pool_heartbeat_callback, this);
	}

	return true;
}


void frame_pool_fini(struct frame_pool * this)
{
	assert(this != NULL);

	while(this->zones != NULL)
	{
		struct ft_poolzone * zone = this->zones;
		this->zones = zone->next;

		_ft_poolzone_del(zone);
	}

	//TODO: Unregister heartbeat
}


struct frame * frame_pool_borrow_real(struct frame_pool * this, uint64_t frame_type, const char * file, unsigned int line)
{
	assert(this != NULL);
	struct frame * frame =  NULL;
	struct ft_poolzone ** last_zone_next = &this->zones;

	// Borrow from existing zone
	for (struct ft_poolzone * zone = this->zones; zone != NULL; zone = zone->next)
	{
		frame = _ft_poolzone_borrow(zone, frame_type, file, line);
		if (frame != NULL) return frame;

		last_zone_next = &zone->next;
	}

	*last_zone_next = this->alloc_fnct(this);
	if (*last_zone_next == NULL)
	{
		FT_WARN("Frame pool ran out of memory");
		return NULL;
	}

	frame = _ft_poolzone_borrow(*last_zone_next, frame_type, file, line);
	if (frame == NULL)
	{
		FT_WARN("Frame pool ran out of memory (2)");
		return NULL;
	}

	return frame;
}


void ft_pool_set_alloc(struct frame_pool * this, ft_pool_alloc_fnct alloc_fnct)
{
	if (alloc_fnct == NULL) this->alloc_fnct = ft_pool_alloc_default;
	else this->alloc_fnct = alloc_fnct;
}


static void frame_pool_heartbeat_callback(struct ft_context * context, void * data)
{
	struct frame_pool * this = (struct frame_pool *)data;
	assert(this != NULL);

	ev_tstamp now = ev_now(context->ev_loop);

	// Iterate via zones and find free-able ones with no used frames ...
	struct ft_poolzone ** last_zone_next = &this->zones;
	struct ft_poolzone * zone = this->zones;
	while (zone != NULL)
	{
		if ((!zone->flags.freeable) || (zone->frames_used > 0))
		{
			last_zone_next = &zone->next;
			zone = zone->next;
			continue;
		}

		if (zone->flags.free_on_hb)
		{
			zone->free_at = now + ft_config.fpool_zone_free_timeout;
			zone->flags.free_on_hb = false;

			last_zone_next = &zone->next;
			zone = zone->next;
			continue;
		}

		if (zone->free_at >= now)
		{
			last_zone_next = &zone->next;
			zone = zone->next;
			continue;			
		}

		// Unchain the zone
		struct ft_poolzone * zone_free = zone;
		zone = zone->next;
		*last_zone_next = zone;

		// Delete zone
		_ft_poolzone_del(zone_free);
	}
}


size_t frame_pool_available_frames_count(struct frame_pool * this)
{
	assert(this != NULL);
	size_t count = 0;

	for (struct ft_poolzone * zone = this->zones; zone != NULL; zone = zone->next)
	{
		count += zone->frames_total - zone->frames_used;
	}

	return count;
}

size_t frame_pool_zones_count(struct frame_pool * this)
{
	assert(this != NULL);
	size_t count = 0;

	for (struct ft_poolzone * zone = this->zones; zone != NULL; zone = zone->next)
	{
		count += 1;
	}

	return count;
}