/* Filter.h

   Copyright (C) 2014 - 2019 Marc Postema (mpostema09 -at- gmail.com)

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
#ifndef MPEGTS_FILTER_H_INCLUDE
#define MPEGTS_FILTER_H_INCLUDE MPEGTS_FILTER_H_INCLUDE

#include <base/Mutex.h>
#include <mpegts/PAT.h>
#include <mpegts/PCR.h>
#include <mpegts/PidTable.h>
#include <mpegts/PMT.h>
#include <mpegts/SDT.h>

namespace mpegts {

/// The class @c Filter carries the PID Tables
class Filter {
		// =====================================================================
		//  -- Constructors and destructor -------------------------------------
		// =====================================================================
	public:

		Filter();

		virtual ~Filter();

		// =====================================================================
		//  -- Other member functions ------------------------------------------
		// =====================================================================
	public:

		///
		void clear();

		///
		void addData(int streamID, const unsigned char *ptr);

		///
		bool isMarkedAsPMT(int pid) const {
			base::MutexLock lock(_mutex);
			return _pat->isMarkedAsPMT(pid);
		}

		///
		bool isMarkedAsActivePMT(int pid) const;

		///
		mpegts::SpPMT getPMTData() const {
			base::MutexLock lock(_mutex);
			return _pmt;
		}

		///
		mpegts::SpPCR getPCRData() const {
			base::MutexLock lock(_mutex);
			return _pcr;
		}

		///
		mpegts::SpPAT getPATData() const {
			base::MutexLock lock(_mutex);
			return _pat;
		}

		///
		mpegts::SpSDT getSDTData() const {
			base::MutexLock lock(_mutex);
			return _sdt;
		}

		// =====================================================================
		// =====================================================================

		/// Set DMX file descriptor
		void setDMXFileDescriptor(int pid, int fd);

		/// Get DMX file descriptor
		int getDMXFileDescriptor(int pid) const;

		/// Close DMX file descriptor and reset data, but keep used flag
		void closeDMXFileDescriptor(int pid);

		/// Reset 'PID has changed' flag
		void resetPIDTableChanged();

		/// Check the 'PID has changed' flag
		bool hasPIDTableChanged() const;

		/// Get the amount of packet that were received of this pid
		uint32_t getPacketCounter(int pid) const;

		/// Get the CSV of all the requested PID
		std::string getPidCSV() const;

		/// Set pid used or not
		void setPID(int pid, bool val);

		/// Check if this pid should be closed
		bool shouldPIDClose(int pid) const;

		/// Check if PID is used
		bool isPIDUsed(int pid) const;

		/// Set all PID
		void setAllPID(bool val);

		// =====================================================================
		//  -- Data members ----------------------------------------------------
		// =====================================================================
	private:

		mutable base::Mutex _mutex;

		mutable mpegts::PidTable _pidTable;
		mutable mpegts::SpPAT _pat;
		mutable mpegts::SpPCR _pcr;
		mutable mpegts::SpPMT _pmt;
		mutable mpegts::SpSDT _sdt;
};

} // namespace mpegts

#endif // MPEGTS_FILTER_H_INCLUDE
