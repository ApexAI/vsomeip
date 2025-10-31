// Copyright (C) 2020-2023 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifdef __QNX__
#ifndef VSOMEIP_V3_QNX_HELPER_HPP_
#define VSOMEIP_V3_QNX_HELPER_HPP_
#include <sys/socket.h>
#if defined(USE_QNX_IO_SOCK) && defined(QNX710)
#include <io-sock/netinet/in.h>
#else
// struct in_pktinfo is defined in qcc71 toolchain
#include <netinet/in.h>
#endif

#ifdef USE_QNX_IO_SOCK
// in_pktinfo must be defined for io-sock
struct in_pktinfo {
    struct in_addr ipi_addr; /* src/dst address */
    unsigned int ipi_ifindex; /* interface index */
};
#endif

#define SO_BINDTODEVICE 0x0800 /* restrict traffic to an interface */
#define IP_PKTINFO		25 /* int; send interface and src addr */

/* Structure used for IP_PKTINFO.  */
#ifndef _STRUCT_IN_PKTINFO
struct in_pktinfo {
    int ipi_ifindex; /* Interface index  */
    struct in_addr ipi_spec_dst; /* Routing destination address  */
    struct in_addr ipi_addr; /* Header destination address  */
};
#define _STRUCT_IN_PKTINFO
#endif

#endif // VSOMEIP_V3_QNX_HELPER_HPP_

#endif
