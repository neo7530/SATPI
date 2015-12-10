/* HttpStreamThread.h

   Copyright (C) 2015 Marc Postema (mpostema09 -at- gmail.com)

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   Or, point your browser to http://www.gnu.org/copyleft/gpl.html
*/
#ifndef HTTP_STREAM_THREAD_H_INCLUDE
#define HTTP_STREAM_THREAD_H_INCLUDE HTTP_STREAM_THREAD_H_INCLUDE

#include "StreamThreadBase.h"
#include "RtcpThread.h"

// forward declaration
class StreamClient;
class StreamProperties;
class DvbapiClient;

/// HTTP Streaming thread
class HttpStreamThread :
		public StreamThreadBase {
	public:
		// =======================================================================
		// Constructors and destructor
		// =======================================================================
		HttpStreamThread(StreamClient *clients, StreamProperties &properties, DvbapiClient *dvbapi);

		virtual ~HttpStreamThread();

		/// @see StreamThreadBase
		virtual bool startStreaming(int fd_dvr, int fd_fe);

	protected:

		/// Thread function
		virtual void threadEntry();

		/// @see StreamThreadBase
		virtual void sendTSPacket(TSPacketBuffer &buffer, const StreamClient &client);

		/// @see StreamThreadBase
		virtual int getStreamSocketPort(int clientID) const;

	private:

		// =======================================================================
		// Data members
		// =======================================================================

}; // class HttpStreamThread

#endif // HTTP_STREAM_THREAD_H_INCLUDE