/*-
 * Copyright (c) 2009 Kai Wang
 * Copyright (c) 2007,2008 Hyogeol Lee <hyogeollee@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	__LIBELFTC_H_
#define	__LIBELFTC_H_

#include <stdbool.h>

/** @brief Dynamic vector data for string. */
struct vector_str {
	/** Current size */
	size_t		size;
	/** Total capacity */
	size_t		capacity;
	/** String array */
	char		**container;
};

#define BUFFER_GROWFACTOR	1.618
#define VECTOR_DEF_CAPACITY	8
#define	ELFTC_ISDIGIT(C) 	(isdigit((C) & 0xFF))

void	vector_str_dest(struct vector_str *);
int	vector_str_find(const struct vector_str *v, const char *o, size_t l);
char	*vector_str_get_flat(const struct vector_str *v, size_t *l);
bool	vector_str_init(struct vector_str *);
bool	vector_str_pop(struct vector_str *);
bool	vector_str_push(struct vector_str *, const char *, size_t);
bool	vector_str_push_vector_head(struct vector_str *dst,
	    struct vector_str *org);
char	*vector_str_substr(const struct vector_str *v, size_t begin, size_t end,
	    size_t *r_len);
char	*cpp_demangle_gnu3(const char *);
bool	is_cpp_mangled_gnu3(const char *);
char	*cpp_demangle_gnu2(const char *);
bool	is_cpp_mangled_gnu2(const char *);
char	*cpp_demangle_ARM(const char *);
bool	is_cpp_mangled_ARM(const char *);

/*
 * Symbols that are sometimes missing from system headers.
 *
 * TODO: Move these to a project-wide file.
 */

#ifndef	EM_AVR
#define	EM_AVR		83
#endif

#endif	/* __LIBELFTC_H */
