
#include <sstream>

#include "emapi.h"
#include "TagwireDecoder.h"
#include "TagwireEncoder.h"
#include "EmapiTypes.h"

using std::string;
using std::stringstream;

namespace emapi
{

MessageDataIf * getMessageClass( const int pClassId ) 
{
	switch( pClassId ) 
	{
	case EmapiMessageType_EmapiAbstractMeEvent:
		return new EmapiAbstractMeEvent();
	case EmapiMessageType_EmapiProteusRefDataMessage:
		return new EmapiProteusRefDataMessage();
	
//	case EmapiMessageType_EmapiOrderInsertReq:
//		return new EmapiOrderInsertReq();
//	case EmapiMessageType_EmapiOrderCancelReq:
//		return new EmapiOrderCancelReq();
//	case EmapiMessageType_EmapiOrderUpdateReq:
//		return new EmapiOrderUpdateReq();
	case EmapiMessageType_EmapiTaxPreLogonReq:
		return new EmapiTaxPreLogonReq();
	case EmapiMessageType_EmapiTaxPreLogonRsp:
		return new EmapiTaxPreLogonRsp();
//	case EmapiMessageType_EmapiTaxLogoutReq:
//		return new EmapiTaxLogoutReq();
//
//	case EmapiMessageType_EmapiOrderInsertRsp:
//		return new EmapiOrderInsertRsp();
//	case EmapiMessageType_EmapiOrderCancelRsp:
//		return new EmapiOrderCancelRsp();
//	case EmapiMessageType_EmapiOrderUpdateRsp:
//		return new EmapiOrderUpdateRsp();
//	case EmapiMessageType_EmapiTaxLogonRsp:
//		return new EmapiTaxLogonRsp();
//	case EmapiMessageType_EmapiTaxPreLogonRsp:
//		return new EmapiTaxPreLogonRsp();
//	case EmapiMessageType_EmapiTaxLogoutRsp:
//		return new EmapiTaxLogoutRsp();
//
	case EmapiMessageType_EmapiTaxConnectorEntry:
		return new EmapiTaxConnectorEntry();
//	case EmapiMessageType_EmapiResponseMessage:
//		return new EmapiResponseMessage();
	case EmapiMessageType_EmapiSimpleRsp:
		return new EmapiSimpleRsp();
	}
	return NULL;
}

/* -------------------------------------------------
 */
EmapiAbstractMeEvent::EmapiAbstractMeEvent()
{	
	mSubscriptionGroup = NULL;
	mSequenceNumber = NULL;
	mTimeOfEvent = NULL;
	mSequenceIndicator = 0L;
}

//EmapiAbstractMeEvent::EmapiAbstractMeEvent(const EmapiAbstractMeEvent & pObject )
//{	
//	mPossDup = false;
////	copy( pObject );
//}


EmapiAbstractMeEvent::~EmapiAbstractMeEvent()
{
}

const string EmapiAbstractMeEvent::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n" ;
	ss << indent << "mSubscriptionGroup: " << mSubscriptionGroup << "\n";
	ss << indent << "mSequenceNumber: " << mSequenceNumber << "\n";
	ss << indent << "mTimeOfEvent: " << mTimeOfEvent << "\n";
	ss << indent << "mSequenceIndicator: " << mSequenceIndicator << "\n";

	string ret = ss.str();
	return ret;
}

//void EmapiAbstractMeEvent::copy(const EmapiAbstractMeEvent & pObject )
//{
//	if (this == &pObject)
//		return;	
//}

const int EmapiAbstractMeEvent::getMessageType() const
{
	return EmapiMessageType_EmapiAbstractMeEvent;
}


//void EmapiAbstractMeEvent::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiAbstractMeEvent::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch(tTag) {
		case 1:
			pDecoder.readInteger(mSubscriptionGroup);
			mSubscriptionGroup = copyAttribute( mSubscriptionGroup );
			break;
		case 2:
			pDecoder.readLong(mSequenceNumber);
			break;
		case 3:
			pDecoder.readString(mTimeOfEvent);
			break;
		case 4:
			pDecoder.readBoolean(mSequenceIndicator);
			mSequenceIndicator = copyAttribute( mSequenceIndicator );
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiAbstractMeEvent::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendInteger(1, mSubscriptionGroup);
	pEncoder.appendLong(2, mSequenceNumber);
	pEncoder.appendString(3, mTimeOfEvent);
	pEncoder.appendBoolean(4, mSequenceIndicator);
	pEncoder.endGroup();
}

const int EmapiAbstractMeEvent::getClassId() const
{
	return 238;
}

const string EmapiAbstractMeEvent::getMessageName() const
{
	return "EmapiAbstractMeEvent";
}


/* -------------------------------------------------
 */
EmapiProteusRefDataMessage::EmapiProteusRefDataMessage()
{	
	mKey = NULL;
	mCacheId = NULL;
	mAction = NULL;
	mStateSequenceNumber = 0L;
	mUniqueObjectId = NULL;
	mTimeStamp = NULL;
	mIsDeleted = NULL;
}

//EmapiProteusRefDataMessage::EmapiProteusRefDataMessage(const EmapiProteusRefDataMessage & pObject )
//{	
//	mPossDup = false;
////	copy( pObject );
//}


EmapiProteusRefDataMessage::~EmapiProteusRefDataMessage()
{
}

const string EmapiProteusRefDataMessage::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n"; 
	ss << indent << "mKey: " << mKey << "\n";
	ss << indent << "mCacheId: " << mCacheId << "\n";
	ss << indent << "mStateSequenceNumber: " << mStateSequenceNumber << "\n";
	ss << indent << "mUniqueObjectId: " << mUniqueObjectId << "\n";
	ss << indent << "mTimeStamp: " << mTimeStamp << "\n";
	ss << indent << "mIsDeleted: " << mIsDeleted << "\n";

	string ret = ss.str();
	return ret;
}

//void EmapiProteusRefDataMessage::copy(const EmapiProteusRefDataMessage & pObject )
//{
//	if (this == &pObject)
//		return;	
//}

const int EmapiProteusRefDataMessage::getMessageType() const
{
	return EmapiMessageType_EmapiProteusRefDataMessage;
}


//void EmapiProteusRefDataMessage::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiProteusRefDataMessage::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch(tTag) {
		case 1:
			pDecoder.readString(mKey);
			break;
		case 2:
			pDecoder.readString(mCacheId);
			break;
		case 3:
			pDecoder.readInteger( mAction );
			mAction = copyAttribute( mAction );
			break;
		case 4:
			pDecoder.readLong(mStateSequenceNumber);
			break;
		case 5:
			pDecoder.readString(mUniqueObjectId);
			break;

		case 6:
			pDecoder.readString(mTimeStamp);
			break;
		case 7:
			pDecoder.readBoolean(mIsDeleted);
			mIsDeleted = copyAttribute( mIsDeleted );
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiProteusRefDataMessage::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendString(1, mKey);
	pEncoder.appendString(2, mCacheId);
	pEncoder.appendInteger(3, mAction);
	pEncoder.appendLong(4, mStateSequenceNumber);
	pEncoder.appendString(5, mUniqueObjectId);
	pEncoder.appendString(6, mTimeStamp);
	pEncoder.appendBoolean(7, mIsDeleted);
	pEncoder.endGroup();
}

const int EmapiProteusRefDataMessage::getClassId() const
{
	return 236;
}

const string EmapiProteusRefDataMessage::getMessageName() const
{
	return "EmapiProteusRefDataMessage";
}


/* -------------------------------------------------
 */
EmapiRequestMessage::EmapiRequestMessage()
{	
	mPossDup = false;
}

//EmapiRequestMessage::EmapiRequestMessage(const EmapiRequestMessage & pObject )
//{	
//	mPossDup = false;
////	copy( pObject );
//}


EmapiRequestMessage::~EmapiRequestMessage()
{
}

const string EmapiRequestMessage::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n" 
	<< indent << "mPossDup: " << mPossDup << "\n";
	
	string ret = ss.str();
	return ret;
}

//void EmapiRequestMessage::copy(const EmapiRequestMessage & pObject )
//{
//	if (this == &pObject)
//		return;	
//}

const int EmapiRequestMessage::getMessageType() const
{
	return EmapiMessageType_EmapiRequestMessage;
}


//void EmapiRequestMessage::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiRequestMessage::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readBoolean(mPossDup);
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiRequestMessage::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendBoolean(1, mPossDup);
	pEncoder.endGroup();
}

const int EmapiRequestMessage::getClassId() const
{
	return 237;
}

const string EmapiRequestMessage::getMessageName() const
{
	return "EmapiRequestMessage";
}

/* -------------------------------------------------
 */

EmapiSimpleRsp::EmapiSimpleRsp()
{
	mReply = NULL;
}

//EmapiSimpleRsp::EmapiSimpleRsp(const EmapiSimpleRsp & pObject )
//{	
//	mPossDup = false;
////	copy( pObject );
//}


EmapiSimpleRsp::~EmapiSimpleRsp()
{
	// TODO
}

const string EmapiSimpleRsp::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n" 
	<< indent << "mReply: " << mReply << "\n";
	string ret = ss.str();
	return ret;
}

//void EmapiSimpleRsp::copy(const EmapiSimpleRsp & pObject )
//{
//	if (this == &pObject)
//		return;	
//}

const int EmapiSimpleRsp::getMessageType() const
{
	return EmapiMessageType_EmapiSimpleRsp;
}


//void EmapiSimpleRsp::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiSimpleRsp::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readInteger(mCode);
			break;
		case 2:
			pDecoder.readString(mMessage);
			break;
		case 3:
			mSubCode = pDecoder.readArrayInt32(mSubCode);
			break;
		case 4:
			pDecoder.readString(mRequestId);
			break;
		case 5:
			pDecoder.readString(mReply);
			break;
		case 6:
			pDecoder.readString(mMessageReference);
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiSimpleRsp::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendInteger(1, mCode);
	pEncoder.appendString(2, mMessage);
	pEncoder.appendArrayInt32(3, mSubCode);
	pEncoder.appendString(4, mRequestId);
	pEncoder.appendString(5, mReply);
	pEncoder.appendString(6, mMessageReference);
	pEncoder.endGroup();
}

const int EmapiSimpleRsp::getClassId() const
{
	return 231;
}

const string EmapiSimpleRsp::getMessageName() const
{
	return "EmapiSimpleRsp";
}





/* -------------------------------------------------
 */

EmapiResponseMessage::EmapiResponseMessage()
{
	mCode = 0;
	mMessage = NULL;
	mSubCode = NULL;
	mRequestId = NULL;
	mMessageReference = NULL;	
}

//EmapiResponseMessage::EmapiResponseMessage(const EmapiResponseMessage & pObject )
//{	
//	mPossDup = false;
////	copy( pObject );
//}


EmapiResponseMessage::~EmapiResponseMessage()
{
	// TODO
}

const string EmapiResponseMessage::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n" 
	<< indent << "mCode: " << mCode << "\n"
	<< indent << "mMessage: " << mMessage << "\n"
	<< indent << "mSubCode: " << mSubCode << "\n"
	<< indent << "mRequestId: " << mRequestId << "\n"
	<< indent << "mMessageReference: " << mMessageReference << "\n"
	;
	string ret = ss.str();
	return ret;
}

//void EmapiResponseMessage::copy(const EmapiResponseMessage & pObject )
//{
//	if (this == &pObject)
//		return;	
//}

const int EmapiResponseMessage::getMessageType() const
{
	return EmapiMessageType_EmapiResponseMessage;
}


//void EmapiResponseMessage::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiResponseMessage::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readInteger(mCode);
			break;
		case 2:
			pDecoder.readString(mMessage);
			break;
		case 3:
			mSubCode = pDecoder.readArrayInt32(mSubCode);
			break;
		case 4:
			pDecoder.readString(mRequestId);
			break;
		case 5:
			pDecoder.readString(mMessageReference);
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiResponseMessage::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendInteger(1, mCode);
	pEncoder.appendString(2, mMessage);
	pEncoder.appendArrayInt32(3, mSubCode);
	pEncoder.appendString(4, mRequestId);
	pEncoder.appendString(5, mMessageReference);
	pEncoder.endGroup();
}

const int EmapiResponseMessage::getClassId() const
{
	return 230;
}

const string EmapiResponseMessage::getMessageName() const
{
	return "EmapiResponseMessage";
}




/* -------------------------------------------------
 */
EmapiTaxPreLogonReq::EmapiTaxPreLogonReq()
{
	mMember = NULL;
	mUser = NULL;
	mMajorVersion = 0;
	mMinorVersion = 0;
	mMicroVersion = 0;
}

EmapiTaxPreLogonReq::~EmapiTaxPreLogonReq()
{
	if ( mMember != NULL ) {
		delete mMember;
	}
	if ( mUser != NULL ) {
		delete mUser;
	}
}

const string EmapiTaxPreLogonReq::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n"
	<< static_cast<EmapiRequestMessage>(*this).to_string( indent + "    " ) << "\n"
	<< indent << "mMember: " << (( mMember ) ? *mMember : string( "null" )) << "\n" 
	<< indent << "mUser: " << (( mUser ) ? *mUser : string( "null" )) << "\n"
	<< indent << "mMajorVersion: " << mMajorVersion << "\n" << "\n"
	<< indent << "mMinorVersion: " << mMinorVersion << "\n"
	<< indent << "mMicroVersion: " << mMicroVersion << "\n";

	string ret = ss.str();
	return ret;
}

const int EmapiTaxPreLogonReq::getMessageType() const
{
	return EmapiMessageType_EmapiTaxPreLogonReq;
}


//void EmapiTaxPreLogonReq::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiTaxPreLogonReq::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readBoolean(mPossDup);
			break;
		case 2:
			pDecoder.readString(mMember);
			break;
		case 3:
			pDecoder.readString(mUser);
			break;
		case 4:
			pDecoder.readInteger(mMajorVersion);
			break;
		case 5:
			pDecoder.readInteger(mMinorVersion);
			break;
		case 6:
			pDecoder.readInteger(mMicroVersion);
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiTaxPreLogonReq::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendBoolean(1, mPossDup);
	pEncoder.appendString(2, mMember);
	pEncoder.appendString(3, mUser);
	pEncoder.appendInteger(4, mMajorVersion);
	pEncoder.appendInteger(5, mMinorVersion);
	pEncoder.appendInteger(6, mMicroVersion);
	pEncoder.endGroup();
}

const int EmapiTaxPreLogonReq::getClassId() const
{
	return 66;
}

const string EmapiTaxPreLogonReq::getMessageName() const
{
	return "EmapiTaxPreLogonReq";
}
/* -------------------------------------------------
 */
EmapiTaxConnectorEntry::EmapiTaxConnectorEntry()
{
	mIpPort = 0;
	mIpAddress = NULL;
	mLoginTicket = NULL;
	mSessionTypes = NULL;
	mSubscriptionGroups = NULL;
}

EmapiTaxConnectorEntry::~EmapiTaxConnectorEntry()
{
	// TODO
}

const string EmapiTaxConnectorEntry::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n"
	   << indent << "mIpPort: " << mIpPort << "\n" 
	   << indent << "mIpAddress: ";  if ( mIpAddress ) ss << *mIpAddress << "\n"; else ss << string("null") << "\n" ;
	ss << indent << "mLoginTicket: ";   if ( mLoginTicket ) ss << *mLoginTicket << "\n" ; else ss << 0 << "\n" ;
	ss << indent << "mSessionTypes: ";   if ( mSessionTypes ) { for (auto x: *mSessionTypes) ss << x << " " ; ss << "\n"; } else ss << 0 << "\n" ; 
	ss << indent << "mSubscriptionGroups: "; if ( mSubscriptionGroups ) { for (auto x: *mSubscriptionGroups) ss << x << " " ; ss << "\n"; } else ss << 0 << "\n" ; 
	ss << indent << "\n";

	string ret = ss.str();
	return ret;
}

const int EmapiTaxConnectorEntry::getMessageType() const
{
	return EmapiMessageType_EmapiTaxConnectorEntry;
}


//void EmapiTaxConnectorEntry::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiTaxConnectorEntry::unpack(TagwireDecoder& pDecoder)
{
LLL
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readInteger(mIpPort);
			break;
		case 2:
			pDecoder.readString(mIpAddress);
			break;
		case 3:
			pDecoder.readLong(mLoginTicket);
			mLoginTicket = copyAttribute(mLoginTicket);
			break;
		case 4:
			mSessionTypes = pDecoder.readArrayInt32(mSessionTypes);
			break;
		case 5:
			mSubscriptionGroups = pDecoder.readArrayInt32(mSubscriptionGroups);
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiTaxConnectorEntry::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendInteger(1, mIpPort);
	pEncoder.appendString(2, mIpAddress);
	pEncoder.appendLong(3, mLoginTicket);
	pEncoder.appendArrayInt32(4, mSessionTypes);
	pEncoder.appendArrayInt32(5, mSubscriptionGroups);
	pEncoder.endGroup();
}

const int EmapiTaxConnectorEntry::getClassId() const
{
	return 68;
}

const string EmapiTaxConnectorEntry::getMessageName() const
{
	return "EmapiTaxConnectorEntry";
}


/* -------------------------------------------------
 */
EmapiTaxPreLogonRsp::EmapiTaxPreLogonRsp()
{
	mAddress = NULL;
	mPort = NULL;
	mTicket = NULL;
	mTaxConnectors = NULL;
}

EmapiTaxPreLogonRsp::~EmapiTaxPreLogonRsp()
{
	// TODO
}

const string EmapiTaxPreLogonRsp::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n"
	<< static_cast<EmapiResponseMessage>(*this).to_string( indent + "    " ) << "\n";
	ss << indent << "mPort: " ; // << (( mPort ) ? *mPort : string( "null" )) << "\n" 
	ss << indent << "mTicket: " ; // << (( mTicket ) ? *mTicket : string( "null" )) << "\n" 
	ss << indent << "mTaxConnectors: " << "\n"; // << (( mTaxConnectors ) ? *mTaxConnectors : string( "null" )) << "\n" 
	;

	string ret = ss.str();
	return ret;
}

const int EmapiTaxPreLogonRsp::getMessageType() const
{
	return EmapiMessageType_EmapiTaxPreLogonRsp;
}


//void EmapiTaxPreLogonRsp::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiTaxPreLogonRsp::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readInteger(mCode);
			break;
		case 2:
			pDecoder.readString(mMessage);
			break;
		case 3:
			mSubCode = pDecoder.readArrayInt32(mSubCode);
			break;
		case 4:
			pDecoder.readString(mRequestId);
			break;
		case 5:
			pDecoder.readString(mReply);
			break;
		case 6:
			pDecoder.readString(mAddress);
			break;
		case 7:
			pDecoder.readInteger(mPort);
			mPort = copyAttribute(mPort);
			break;
		case 8:
			pDecoder.readLong(mTicket);
				mTicket = copyAttribute(mTicket);
			break;
		case 9:
			pDecoder.readArray(mTaxConnectors);
			break;
		case 10:
			pDecoder.readString(mMessageReference);
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiTaxPreLogonRsp::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendInteger(1, mCode);
	pEncoder.appendString(2, mMessage);
	pEncoder.appendArrayInt32(3, mSubCode);
	pEncoder.appendString(4, mRequestId);
	pEncoder.appendString(5, mReply);
	pEncoder.appendString(6, mAddress);
	pEncoder.appendInteger(7, mPort);
	pEncoder.appendLong(8, mTicket);
	pEncoder.appendArray(9, mTaxConnectors);
	pEncoder.appendString(10, mMessageReference);
	pEncoder.endGroup();
}

const int EmapiTaxPreLogonRsp::getClassId() const
{
	return 67;
}

const string EmapiTaxPreLogonRsp::getMessageName() const
{
	return "EmapiTaxPreLogonRsp";
}


/* -------------------------------------------------
 */
EmapiTaxLogonRsp::EmapiTaxLogonRsp()
{
	mLogonAccepted = NULL;
	mLoginStatus = 0;
	mIsTestSystem = NULL;
	mSystemName = NULL;
	mPartitionHbtInterval = NULL;
	mClientHbtInterval = NULL;
	mMaxLostHeartbeats =  NULL;
	mPublicMulticastContent  = NULL;
}

EmapiTaxLogonRsp::~EmapiTaxLogonRsp()
{
	// TODO
}

const string EmapiTaxLogonRsp::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n";
	ss << indent << "mLogonAccepted: " << "\n";;  //  if ( mLogonAccepted ) ss << *mLogonAccepted << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mLoginStatus: " << "\n";;  //  if ( mLoginStatus ) ss << *mLoginStatus << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mIsTestSystem: " << "\n";;  //  if ( mIsTestSystem ) ss << *mIsTestSystem << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mSystemName: " << "\n";;  //  if ( msystemName ) ss << *msystemName << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mPartitionHbtInterval: " << "\n";;  //  if ( mPartitionHbtInterval ) ss << *mPartitionHbtInterval << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mClientbtInterval: " << "\n";;  //  if ( mClientbtInterval ) ss << *mClientbtInterval << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mMaxLostHeartbeats: " << "\n";;  //  if ( mMaxLostHeartbeats ) ss << *mMaxLostHeartbeats << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mPublicMulticastContent: " << "\n";;  //  if ( mPublicMulticastContent ) ss << *mPublicMulticastContent << "\n";    else ss << string("null") << "\n" ;

	string ret = ss.str();
	return ret;
}

const int EmapiTaxLogonRsp::getMessageType() const
{
	return EmapiMessageType_EmapiTaxLogonRsp;
}


//void EmapiTaxLogonRsp::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiTaxLogonRsp::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readInteger(mCode);
			break;
		case 2:
			pDecoder.readString(mMessage);
			break;
		case 3:
			mSubCode = pDecoder.readArrayInt32(mSubCode);
			break;
		case 4:
			pDecoder.readString(mRequestId);
			break;
		case 5:
			pDecoder.readString(mReply);
			break;
		case 6:
			pDecoder.readBoolean(mLogonAccepted);
			mLogonAccepted = copyAttribute(mLogonAccepted);
			break;
		case 7:
			pDecoder.readInteger(mLoginStatus);
			break;
		case 8:
			pDecoder.readBoolean(mIsTestSystem);
			mIsTestSystem = copyAttribute(mIsTestSystem);
			break;
		case 9:
			pDecoder.readString(mSystemName);
			break;

		case 10:
			pDecoder.readInteger(mPartitionHbtInterval);
			mPartitionHbtInterval = copyAttribute(mPartitionHbtInterval);
			break;
		case 11:
			pDecoder.readInteger(mClientHbtInterval);
			mClientHbtInterval = copyAttribute(mClientHbtInterval);
			break;
		case 12:
			pDecoder.readInteger(mMaxLostHeartbeats);
			mMaxLostHeartbeats = copyAttribute(mMaxLostHeartbeats);
			break;
		case 13:
			pDecoder.readArray(mPublicMulticastContent);
			break;
		case 14:
			pDecoder.readString(mMessageReference);
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiTaxLogonRsp::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendInteger(1, mCode);
	pEncoder.appendString(2, mMessage);
	pEncoder.appendArrayInt32(3, mSubCode);
	pEncoder.appendString(4, mRequestId);
	pEncoder.appendString(5, mReply);
	pEncoder.appendBoolean(6, mLogonAccepted);
	pEncoder.appendInteger(7, mLoginStatus);
	pEncoder.appendBoolean(8, mIsTestSystem);
	pEncoder.appendString(9, mSystemName);
	pEncoder.appendInteger(10, mPartitionHbtInterval);
	pEncoder.appendInteger(11, mClientHbtInterval);
	pEncoder.appendInteger(12, mMaxLostHeartbeats);
	pEncoder.appendArray(13, mPublicMulticastContent);
	pEncoder.appendString(14, mMessageReference);
	pEncoder.endGroup();
}

const int EmapiTaxLogonRsp::getClassId() const
{
	return 64;
}

const string EmapiTaxLogonRsp::getMessageName() const
{
	return "EmapiTaxLogonRsp";
}


/* -------------------------------------------------
 */
EmapiPublicMulticastContent::EmapiPublicMulticastContent()
{
	mPmcContentId = NULL;
	mFlowIdList = NULL;
	mSubscriptionGroupList = NULL;
	mPublicMulticastPartitions = NULL;
}

EmapiPublicMulticastContent::~EmapiPublicMulticastContent()
{
}

const string EmapiPublicMulticastContent::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n";

	string ret = ss.str();
	return ret;
}

const int EmapiPublicMulticastContent::getMessageType() const
{
	return EmapiMessageType_EmapiPublicMulticastContent;
}


//void EmapiPublicMulticastContent::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiPublicMulticastContent::unpack(TagwireDecoder& pDecoder)
{

	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readString(mKey);
			break;
		case 2:
			pDecoder.readString(mCacheId);
			break;
		case 3:
			pDecoder.readInteger(mAction);
			mAction = copyAttribute(mAction);
			break;
		case 4:
			pDecoder.readLong(mStateSequenceNumber);
			break;

		case 5:
			pDecoder.readString(mUniqueObjectId);
			break;
		case 6:
			pDecoder.readString(mTimeStamp);
			break;
		case 7:
			pDecoder.readString(mPmcContentId);
			break;
		case 8:
			pDecoder.readString(mFlowIdList);
			break;
		case 9:
			pDecoder.readString(mSubscriptionGroupList);
			break;
		case 10:
			pDecoder.readArray(mPublicMulticastPartitions);
			break;
		case 11:
			pDecoder.readBoolean(mIsDeleted);
			mIsDeleted = copyAttribute( mIsDeleted );
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiPublicMulticastContent::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.appendString(1, mKey);
	pEncoder.appendString(2, mCacheId);
	pEncoder.appendInteger(3, mAction);
	pEncoder.appendLong(4, mStateSequenceNumber);

	pEncoder.appendString(5, mUniqueObjectId);
	pEncoder.appendString(6, mTimeStamp);
	pEncoder.appendString(7, mPmcContentId);
	pEncoder.appendString(8, mFlowIdList);
	pEncoder.appendString(9, mSubscriptionGroupList);
	pEncoder.appendArray(10, mPublicMulticastPartitions);
	pEncoder.appendBoolean(11, mIsDeleted);
	pEncoder.endGroup();
}

const int EmapiPublicMulticastContent::getClassId() const
{
	return 108;
}

const string EmapiPublicMulticastContent::getMessageName() const
{
	return "EmapiPublicMulticastContent";
}
/* -------------------------------------------------
 */
EmapiPublicMulticastPartition::EmapiPublicMulticastPartition()
{
	mPmcPartitionId = NULL;
	mPayloadContentType = NULL;
	mTimeToLive = NULL;
	mBundleSize = NULL;
	mHeartbeatInterval = NULL;
	mPmcContentId = NULL;
	mPublicMulticastAddresses = NULL;
}

EmapiPublicMulticastPartition::~EmapiPublicMulticastPartition()
{
}

const string EmapiPublicMulticastPartition::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n";

	string ret = ss.str();
	return ret;
}

const int EmapiPublicMulticastPartition::getMessageType() const
{
	return EmapiMessageType_EmapiPublicMulticastPartition;
}


//void EmapiPublicMulticastPartition::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiPublicMulticastPartition::unpack(TagwireDecoder& pDecoder)
{

	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readString(mKey);
			break;
		case 2:
			pDecoder.readString(mCacheId);
			break;
		case 3:
			pDecoder.readInteger(mAction);
			mAction = copyAttribute(mAction);
			break;
		case 4:
			pDecoder.readLong(mStateSequenceNumber);
			break;

		case 5:
			pDecoder.readString(mUniqueObjectId);
			break;
		case 6:
			pDecoder.readString(mTimeStamp);
			break;
		case 7:
			pDecoder.readString(mPmcPartitionId);
			break;
		case 8:
			pDecoder.readString(mPayloadContentType);
			break;
		case 10:
			pDecoder.readInteger(mTimeToLive);
			mTimeToLive = copyAttribute(mTimeToLive);
			break;
		case 11:
			pDecoder.readInteger(mBundleSize);
			mBundleSize = copyAttribute(mBundleSize);
			break;
		case 12:
			pDecoder.readInteger(mHeartbeatInterval);
			mHeartbeatInterval = copyAttribute(mHeartbeatInterval);
			break;
		case 13:
			pDecoder.readString(mPmcContentId);
			break;
		case 14:
			pDecoder.readArray(mPublicMulticastAddresses);
			break;
		case 15:
			pDecoder.readBoolean(mIsDeleted);
			mIsDeleted = copyAttribute( mIsDeleted );
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiPublicMulticastPartition::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.appendString(1, mKey);
	pEncoder.appendString(2, mCacheId);
	pEncoder.appendInteger(3, mAction);
	pEncoder.appendLong(4, mStateSequenceNumber);
	pEncoder.appendString(5, mUniqueObjectId);
	pEncoder.appendString(6, mTimeStamp);
	pEncoder.appendString(7, mPmcPartitionId);
	pEncoder.appendString(8, mPayloadContentType);
	pEncoder.appendInteger(10, mTimeToLive);
	pEncoder.appendInteger(11, mBundleSize);
	pEncoder.appendInteger(12, mHeartbeatInterval);
	pEncoder.appendString(13, mPmcContentId);
	pEncoder.appendArray(14, mPublicMulticastAddresses);
	pEncoder.appendBoolean(15, mIsDeleted);
	pEncoder.endGroup();
}

const int EmapiPublicMulticastPartition::getClassId() const
{
	return 109;
}

const string EmapiPublicMulticastPartition::getMessageName() const
{
	return "EmapiPublicMulticastPartition";
}

/* -------------------------------------------------
 */
EmapiPublicMulticastAddress::EmapiPublicMulticastAddress()
{
	mPmcAddress = NULL;
	mPmcPort = NULL;
	mPmcSourceAddress = NULL;
	mPmcPartitionId = NULL;
}

EmapiPublicMulticastAddress::~EmapiPublicMulticastAddress()
{
}

const string EmapiPublicMulticastAddress::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n";

	string ret = ss.str();
	return ret;
}

const int EmapiPublicMulticastAddress::getMessageType() const
{
	return EmapiMessageType_EmapiPublicMulticastAddress;
}


//void EmapiPublicMulticastAddress::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiPublicMulticastAddress::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch( tTag) {
		case 1:
			pDecoder.readString(mKey);
			break;
		case 2:
			pDecoder.readString(mCacheId);
			break;
		case 3:
			pDecoder.readInteger(mAction);
			mAction = copyAttribute(mAction);
			break;
		case 4:
			pDecoder.readLong(mStateSequenceNumber);
			break;

		case 5:
			pDecoder.readString(mUniqueObjectId);
			break;
		case 6:
			pDecoder.readString(mTimeStamp);
			break;
		case 7:
			pDecoder.readString(mPmcAddress);
			break;
		case 8:
			pDecoder.readInteger(mPmcPort);
			mPmcPort = copyAttribute(mPmcPort);
			break;
		case 9:
			pDecoder.readString(mPmcSourceAddress);
			break;
		case 10:
			pDecoder.readString(mPmcPartitionId);
			break;
		case 11:
			pDecoder.readBoolean(mIsDeleted);
			mIsDeleted = copyAttribute( mIsDeleted );
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiPublicMulticastAddress::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.appendString(1, mKey);
	pEncoder.appendString(2, mCacheId);
	pEncoder.appendInteger(3, mAction);
	pEncoder.appendLong(4, mStateSequenceNumber);
	pEncoder.appendString(5, mUniqueObjectId);
	pEncoder.appendString(6, mTimeStamp);
	pEncoder.appendString(7, mPmcAddress);
	pEncoder.appendInteger(8, mPmcPort);
	pEncoder.appendString(10, mPmcSourceAddress);
	pEncoder.appendString(11, mPmcPartitionId);
	pEncoder.appendBoolean(15, mIsDeleted);
	pEncoder.endGroup();
}

const int EmapiPublicMulticastAddress::getClassId() const
{
	return 110;
}

const string EmapiPublicMulticastAddress::getMessageName() const
{
	return "EmapiPublicMulticastAddress";
}


/* -------------------------------------------------
 */
EmapiHeartbeat::EmapiHeartbeat()
{
	mTimestamp = NULL;
	mPartition = NULL;
}

EmapiHeartbeat::~EmapiHeartbeat()
{
}

const string EmapiHeartbeat::to_string(string indent) const
{
	stringstream ss;
	ss << indent << getMessageName() << ":\n";

	string ret = ss.str();
	return ret;
}

const int EmapiHeartbeat::getMessageType() const
{
	return EmapiMessageType_EmapiHeartbeat;
}


//void EmapiHeartbeat::traceMessage(MessageTrace *pTrace, int pLevel) const
//{
//}


void EmapiHeartbeat::unpack(TagwireDecoder& pDecoder)
{
	while( pDecoder.hasMoreTags()) {
		int tTag = pDecoder.getNextTag();
		switch(tTag) {
		case 1:
			pDecoder.readInteger(mSubscriptionGroup);
			mSubscriptionGroup = copyAttribute( mSubscriptionGroup );
			break;
		case 2:
			pDecoder.readLong(mSequenceNumber);
			break;
		case 3:
			pDecoder.readString(mTimeOfEvent);
			break;
		case 4:
			pDecoder.readBoolean(mSequenceIndicator);
			mSequenceIndicator = copyAttribute( mSequenceIndicator );
			break;
		case 5:
			pDecoder.readString(mTimestamp);
			break;
		case 6:
			pDecoder.readInteger(mPartition);
			mPartition = copyAttribute( mPartition );
			break;
		default:
			pDecoder.skipUnknownTag();
			break;
		}
	}
}

void EmapiHeartbeat::pack(TagwireEncoder& pEncoder) const
{
	pEncoder.beginGroup();
	pEncoder.appendInteger(1, mSubscriptionGroup);
	pEncoder.appendLong(2, mSequenceNumber);
	pEncoder.appendString(3, mTimeOfEvent);
	pEncoder.appendBoolean(4, mSequenceIndicator);
	pEncoder.appendString(5, mTimestamp);
	pEncoder.appendInteger(6, mPartition);
	pEncoder.endGroup();
}

const int EmapiHeartbeat::getClassId() const
{
	return 74;
}

const string EmapiHeartbeat::getMessageName() const
{
	return "EmapiHeartbeat";
}


} // namespace

