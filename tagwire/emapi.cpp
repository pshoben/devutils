#include "emapi.h"
#include "TagwireDecoder.h"
#include "TagwireEncoder.h"

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
//	case EmapiMessageType_EmapiTaxLogonReq:
//		return new EmapiTaxLogonReq();
	case EmapiMessageType_EmapiTaxPreLogonReq:
		return new EmapiTaxPreLogonReq();
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
//	case EmapiMessageType_EmapiTaxConnectorEntry:
//		return new EmapiTaxConnectorEntry();
//	case EmapiMessageType_EmapiResponseMessage:
//		return new EmapiResponseMessage();
//	case EmapiMessageType_EmapiSimpleRsp:
//		return new EmapiSimpleRsp();
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

//const string EmapiRequestMessage::toString() const
//{
//	return " EmapiRequestMessage::toString";
//}

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

//const string EmapiTaxPreLogonReq::toString() const
//{
//	return " EmapiTaxPreLogonReq::toString";
//}

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

}

