#ifndef JOLTBODYID
#define JOLTBODYID

//#include "Logger/Logger.h"

#include "JoltHashCombine.h"

namespace TDS
{
DLL_API class JoltBodyID
{
public:
	static constexpr uint32_t	cInvalidBodyID = 0xffffffff;	///< The value for an invalid body ID
	static constexpr uint32_t	cBroadPhaseBit = 0x00800000;	///< This bit is used by the broadphase
	static constexpr uint32_t	cMaxBodyIndex = 0x7fffff;		///< Maximum value for body index (also the maximum amount of bodies supported - 1)
	static constexpr uint32_t	cMaxSequenceNumber = 0xff;		///< Maximum value for the sequence number

	/// Construct invalid body ID
	JoltBodyID() :
		mID(cInvalidBodyID)
	{
	}

	/// Construct from index and sequence number combined in a single uint32_t (use with care!)
	explicit				JoltBodyID(uint32_t inID) :
		mID(inID)
	{
		//TDS_ASSERT(!((inID & cBroadPhaseBit) == 0 || inID == cInvalidBodyID), "inID & cBroadPhaseBit should not be 0 or inID should not be cInvalidBodyID")
		if (!((inID & cBroadPhaseBit) == 0 || inID == cInvalidBodyID))
		{
			throw std::logic_error("inID & cBroadPhaseBit should not be 0 or inID should not be cInvalidBodyID");
		}
	}

	/// Construct from index and sequence number
	explicit				JoltBodyID(uint32_t inID, uint8_t inSequenceNumber) :
		mID((uint32_t(inSequenceNumber) << 24) | inID)
	{
		//TDS_ASSERT(!(inID < cMaxBodyIndex), "IndexID is greater than cMaxBodyIndex")
		if (!(inID < cMaxBodyIndex))
		{
			throw std::logic_error("IndexID is greater than cMaxBodyIndex");
		}
	}

	/// Get index in body array
	inline uint32_t			GetIndex() const
	{
		return mID & cMaxBodyIndex;
	}

	/// Get sequence number of body.
	/// The sequence number can be used to check if a body ID with the same body index has been reused by another body.
	/// It is mainly used in multi threaded situations where a body is removed and its body index is immediately reused by a body created from another thread.
	/// Functions querying the broadphase can (after aquiring a body lock) detect that the body has been removed (we assume that this won't happen more than 128 times in a row).
	inline uint8_t			GetSequenceNumber() const
	{
		return uint8_t(mID >> 24);
	}

	/// Returns the index and sequence number combined in an uint32_t
	inline uint32_t			GetIndexAndSequenceNumber() const
	{
		return mID;
	}

	/// Check if the ID is valid
	inline bool				IsInvalid() const
	{
		return mID == cInvalidBodyID;
	}

	/// Equals check
	inline bool				operator == (const JoltBodyID& inRHS) const
	{
		return mID == inRHS.mID;
	}

	/// Not equals check
	inline bool				operator != (const JoltBodyID& inRHS) const
	{
		return mID != inRHS.mID;
	}

	/// Smaller than operator, can be used for sorting bodies
	inline bool				operator < (const JoltBodyID& inRHS) const
	{
		return mID < inRHS.mID;
	}

	/// Greater than operator, can be used for sorting bodies
	inline bool				operator > (const JoltBodyID& inRHS) const
	{
		return mID > inRHS.mID;
	}

private:
	uint32_t					mID;
};
} // TDS

JOLT_MAKE_HASHABLE(TDS::JoltBodyID, t.GetIndexAndSequenceNumber())

#endif // !JOLTBODYID
