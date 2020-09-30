
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
	   << indent << "mIpAddress: ";  //  if ( mIpAddress ) ss << *mIpAddress << "\n";    else ss << string("null") << "\n" ;
	ss << indent << "mLoginTicket: " ; //if ( mLoginTicket ) ss << *mLoginTicket << "\n" ; else ss << 0 << "\n" ;
	ss << indent << "mSessionTypes: "; //  if ( mSessionTypes ) ss << *mSessionTypes << "\n"; else ss << 0 << "\n" ; 
	ss << indent << "mSubscriptionGroups: "; // if ( mSubscriptionGroups ) ss << *mSubscriptionGroups << "\n"; else ss << string("null") << "\n" ;
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


}

