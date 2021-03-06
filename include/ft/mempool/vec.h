#ifndef FT_MEMPOOL_VEC_H_
#define FT_MEMPOOL_VEC_H_

/****

Frame vectors

+-------------------------------+
|            data space         |
+-------------------------------+ 
|            free space         |
+-------------------------------+
|        vec[-vec_limit-1]      |
+-------------------------------+
|        vec[-vec_limit-2]      |
+-------------------------------+
|              vec[0]           |
+-------------------------------+ <----- capacity 

****/

struct ft_vec
{
	struct ft_frame * frame;

	// 0 (+ offset) <= position <= limit <= capacity
	// Vector length is defined as limit - position

	// 
	// The offset is never negative and is inside a frame
	size_t offset;

	// The position is the index of the next byte to be read or written.
	// The position is never negative and is never greater than its limit.
	size_t position;

	// The limit is the index of the first byte that should not be read or written.
	// The limit is never negative and is never greater than its capacity.
	size_t limit;

	// The capacity is the number of bytes it contains.
	// The capacity is never negative and never changes.
	size_t capacity;
};


static inline void ft_vec_advance(struct ft_vec * this, size_t position_delta)
{
	assert((this->position + position_delta) <= this->limit);
	assert((this->position + position_delta) <= this->capacity);

	this->position += position_delta;
}

static inline void ft_vec_pos(struct ft_vec * this, size_t position)
{
	assert(this->position <= this->limit);
	assert(this->position <= this->capacity);
	this->position = position;
}

static inline void ft_vec_flip(struct ft_vec * this)
{
	this->limit = this->position;
	this->position = 0;	
}

bool ft_vec_sprintf(struct ft_vec * , const char * format, ...);
bool ft_vec_vsprintf(struct ft_vec * , const char * format, va_list ap);
bool ft_vec_strcat(struct ft_vec * , const char * text);
bool ft_vec_cat(struct ft_vec * , const void * data, size_t data_len);

static inline size_t ft_vec_len(struct ft_vec * this)
{
	assert(this != NULL);
	return this->limit - this->position;
}

#endif // FT_MEMPOOL_VEC_H_
