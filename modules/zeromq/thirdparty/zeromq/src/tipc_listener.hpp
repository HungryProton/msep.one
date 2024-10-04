/* SPDX-License-Identifier: MPL-2.0 */

#ifndef __ZMQ_TIPC_LISTENER_HPP_INCLUDED__
#define __ZMQ_TIPC_LISTENER_HPP_INCLUDED__

#include "platform.hpp"

#if defined ZMQ_HAVE_TIPC

#include <string>

#include "fd.hpp"
#include "stream_listener_base.hpp"
#include "tipc_address.hpp"

namespace zmq
{
class tipc_listener_t ZMQ_FINAL : public stream_listener_base_t
{
  public:
    tipc_listener_t (zmq::io_thread_t *io_thread_,
                     zmq::socket_base_t *socket_,
                     const options_t &options_);

    //  Set address to listen on.
    int set_local_address (const char *addr_);

  protected:
    std::string get_socket_name (fd_t fd_,
                                 socket_end_t socket_end_) const ZMQ_FINAL;

  private:
    //  Handlers for I/O events.
    void in_event () ZMQ_FINAL;

    //  Accept the new connection. Returns the file descriptor of the
    //  newly created connection. The function may return retired_fd
    //  if the connection was dropped while waiting in the listen backlog.
    fd_t accept ();

    // Address to listen on
    tipc_address_t _address;

    ZMQ_NON_COPYABLE_NOR_MOVABLE (tipc_listener_t)
};
}

#endif

#endif
