/*
	This file is part of duckOS.

	duckOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	duckOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with duckOS.  If not, see <https://www.gnu.org/licenses/>.

	Copyright (c) Byteduck 2016-2021. All rights reserved.
*/

#pragma once

#include <vector>
#include <string>
#include <libduck/Result.h>
#include <sys/socketfs.h>
#include <poll.h>
#include <cstring>

#define LIBRIVER_PACKET_MAGIC 0xBEEF420
#define LIBRIVER_MAX_TARGET_NAME_LEN 1024

namespace River {
	enum PacketType {
		SOCKETFS_CLIENT_CONNECTED = -1,
		SOCKETFS_CLIENT_DISCONNECTED = -2,

		CLIENT_CONNECTED = 1,
		CLIENT_DISCONNECTED = 2,

		REGISTER_ENDPOINT = 10,
		GET_ENDPOINT = 11,

		FUNCTION_CALL = 20,
		FUNCTION_RETURN = 21,
		REGISTER_FUNCTION = 22,
		GET_FUNCTION = 23,

		REGISTER_MESSAGE = 24,
		GET_MESSAGE = 26,
		SEND_MESSAGE = 25,

		DEREGISTER_PATH = 30
	};

	enum ErrorType {
		SUCCESS = 0,
		UNKNOWN_ERROR = 1,

		ENDPOINT_ALREADY_REGISTERED = 3,
		ENDPOINT_DOES_NOT_EXIST = 4,
		FUNCTION_ALREADY_REGISTERED = 5,
		FUNCTION_DOES_NOT_EXIST = 6,
		MALFORMED_DATA = 7,
		ILLEGAL_REQUEST = 8,
		MESSAGE_ALREADY_REGISTERED = 9,
		MESSAGE_DOES_NOT_EXIST = 10,
		MESSAGE_HANDLER_ALREADY_SET = 11
	};

	const char* error_str(int type);

	struct RawPacket {
		int __river_magic = LIBRIVER_PACKET_MAGIC;
		PacketType type;
		size_t path_length; //Incl. null terminator
		size_t data_length;
		ErrorType error;
		sockid_t id;
		uint8_t data[];
	};

	struct RiverPacket {
		PacketType type;
		std::string endpoint;
		std::string path;
		union {
			ErrorType error;
			pid_t connected_pid;
			pid_t disconnected_pid;
		};
		union {
			sockid_t recipient;
			sockid_t sender;
			sockid_t connected_id;
			sockid_t disconnected_id;
		};
		sockid_t __socketfs_from_id;
		pid_t __socketfs_from_pid;
		std::vector<uint8_t> data;
	};

	enum PacketReadResult {
		PACKET_READ = 0,
		NO_PACKET,
		PACKET_ERR,
		SOCKETFS_MESSAGE,
	};

	Duck::ResultRet<RiverPacket> receive_packet(int fd, bool block);
	Duck::Result send_packet(int fd, sockid_t recipient, const RiverPacket& packet);
}

