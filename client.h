#ifndef _9PCLIENT_H
# define _9PCLIENT_H

// May need to change this
# include "lib9p.h"
# include "fid.h"

# define NOTAG	((uint16_t)(~0))
# define NOFID	((uint32_t)(~0))

/*
 * Similar to l9p_connection, but without the server aspects.
 */
struct l9p_client_connection {
	enum l9p_version lc_version;
	uint32_t	root_fid;
	uint32_t lc_msize;
	uint32_t lc_max_io_size;
	void	*context;
	// Should this deal with tags?
	int	(*send_msg)(struct l9p_client_connection *, struct iovec *iov);
	int	(*recv_msg)(struct l9p_client_connection *, uint16_t tag, union l9p_fcall **response);
	void	*fids;		// context to determine next fid
	void	*tags;		// context to determine next hash
};

int client_pack_message(struct l9p_client_connection *, struct iovec *, union l9p_fcall *);
int client_unpack_message(struct l9p_client_connection *, struct iovec *, union l9p_fcall *);

/*
 * Functions to create a p9 message.
 */
int vp9_msg(struct l9p_client_connection *, union l9p_fcall *msg, enum l9p_ftype type, uint16_t *tagp, va_list ap);
int p9_msg(struct l9p_client_connection *, union l9p_fcall *msg, enum l9p_ftype type, uint16_t *tagp, ...);
int packed_p9_msg(struct l9p_client_connection *, struct iovec *iovc, enum l9p_ftype type, uint16_t *tagp, ...);

/*
 * Functions to handle tags and fids
 */
uint16_t get_tag(struct l9p_client_connection *);
void release_tag(struct l9p_client_connection *, uint16_t);

uint32_t get_fid(struct l9p_client_connection *);
void release_fid(struct l9p_client_connection *, uint32_t);
int talk(struct l9p_client_connection *conn, union l9p_fcall *transmit, union l9p_fcall **response);

#endif /* _9PCLIENT_H */
