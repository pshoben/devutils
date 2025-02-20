#ifndef emapi_H
#define emapi_H

#define LIBEXPORT

#include <iostream>
#include "ByteArray.h"
#include "EmapiTypes.h"
#include "MessageDataIf.h"
#include "TagwireEncoder.h"
#include "TagwireDecoder.h"
#include "MessageTrace.h"

//#include "emapibiginteger.h"

using std::string;
using std::vector;

#define LLL printf("%s : %s:%d\n", __FUNCTION__, __FILE__, __LINE__ );

namespace emapi
{
	class EmapiHeartbeat;
	class EmapiTaxConnectorEntry;
	class EmapiTaxPreLogonReq;
	class EmapiTaxPreLogonRsp;
	class EmapiTaxLogonReq;
	class EmapiTaxLogonRsp;
	class EmapiPublicMulticastAddress;
	class EmapiPublicMulticastContent;
	class EmapiPublicMulticastPartition;
	class EmapiProteusRefDataMessage;
	class EmapiAbstractMeEvent;

	static const int EmapiMessageType_EmapiProteusRefDataMessage = 236;
	static const int EmapiMessageType_EmapiAbstractMeEvent = 238;

	static const int EmapiMessageType_EmapiOrderInsertReq = 1;
	static const int EmapiMessageType_EmapiOrderUpdateReq = 8;
	static const int EmapiMessageType_EmapiOrderCancelReq = 6;

	static const int EmapiMessageType_EmapiOrderInsertRsp = 2;
	static const int EmapiMessageType_EmapiOrderUpdateRsp = 9;
	static const int EmapiMessageType_EmapiOrderCancelRsp = 7;

	static const int EmapiMessageType_EmapiTaxConnectorEntry = 68;

	static const int EmapiMessageType_EmapiTaxPreLogonReq = 66;
	static const int EmapiMessageType_EmapiTaxPreLogonRsp = 67;

	static const int EmapiMessageType_EmapiHeartbeat = 74;
	static const int EmapiMessageType_EmapiTaxHeartbeatReq = 75;
	static const int EmapiMessageType_EmapiTaxHeartbeatRsp = 76;
	
	static const int EmapiMessageType_EmapiTaxLogonReq = 63;
	static const int EmapiMessageType_EmapiTaxLogonRsp = 64;

	static const int EmapiMessageType_EmapiPublicMulticastAddress = 110;
	static const int EmapiMessageType_EmapiPublicMulticastContent = 108;
	static const int EmapiMessageType_EmapiPublicMulticastPartition = 109;

	static const int EmapiMessageType_EmapiRequestMessage = 237;
	static const int EmapiMessageType_EmapiResponseMessage = 230;

	static const int EmapiMessageType_EmapiSimpleRsp = 231;

	static const int EMAPI_TAX_TYPE_ORDER_ENTRY = 1;
	static const int EMAPI_TAX_TYPE_MARKET_DATA = 2;	
	static const int EMAPI_TAX_TYPE_REPLAY = 3;	
	
enum EmapiFlowType {
	Enum_Flow_PUBLIC_PRICELEVEL_FLOW = 1,
	Enum_Flow_PUBLIC_PARTITION_FLOW  =  3
};


class Emapi 
{
	public:
	static MessageDataIf* getMessageClass(const int pClassId);
	string getBdxFlowName(enum EmapiFlowType pBdxFlowId);
	static string getEmapiStatusText(int pStatusCode);
};


class EmapiMessage : public MessageDataIf 
{
public:
	//virtual void copy(const EmapiMessage &pObject);
	ByteArray cXMLDictionary;
	ByteArray cTAPDictionary;
	ByteArray cTapwireDictionary;
	
	EmapiMessage();
	EmapiMessage(const EmapiMessage &pObject);
	
	virtual ~EmapiMessage();
	//const string toString() const;
	const int getMessageType() const;
	//virtual EmapiMessage & operator=(const EmapiMessage & pObject);
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiMessage* clone() const;

	virtual void pack(TagwireEncoder& pEncode);
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId();
	virtual const string getMessageName();	
};

class EmapiResponseMessage : public MessageDataIf 
{
public:
	int32 * mCode;
	string * mMessage;
	vector<int32> * mSubCode;
	string * mRequestId;
	string * mMessageReference;

	//void copy(const EmapiResponseMessage &pObject);
	
	EmapiResponseMessage();
	//EmapiResponseMessage(const EmapiResponseMessage &pObject);
	
	virtual ~EmapiResponseMessage();

	//EmapiResponseMessage & operator=(const EmapiResponseMessage & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiResponseMessage* clone() const;
};

class EmapiSimpleRsp : public EmapiResponseMessage 
{
public:
	string * mReply;
	
	//void copy(const EmapiSimpleRsp &pObject);
	
	EmapiSimpleRsp();
	///EmapiSimpleRsp(const EmapiSimpleRsp &pObject);
	
	virtual ~EmapiSimpleRsp();

	//EmapiSimpleRsp & operator=(const EmapiSimpleRsp & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiSimpleRsp* clone() const;
};

class EmapiRequestMessage : public MessageDataIf 
{
public:
	bool mPossDup;
	
	//void copy(const EmapiRequestMessage &pObject);
	
	EmapiRequestMessage();
	//EmapiRequestMessage(const EmapiRequestMessage &pObject);
	
	virtual ~EmapiRequestMessage();

	//EmapiRequestMessage & operator=(const EmapiRequestMessage & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiRequestMessage* clone() const;
};


class EmapiTaxPreLogonReq : public EmapiRequestMessage 
{
public:
	string * mMember;
	string * mUser;
	int32 mMajorVersion;
	int32 mMinorVersion;
	int32 mMicroVersion;
	
	//void copy(const EmapiTaxPreLogonReq &pObject);
	
	EmapiTaxPreLogonReq();
	//EmapiTaxPreLogonReq(const EmapiTaxPreLogonReq &pObject);
	
	virtual ~EmapiTaxPreLogonReq();

	//EmapiTaxPreLogonReq & operator=(const EmapiTaxPreLogonReq & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiTaxPreLogonReq* clone() const;
};


class EmapiTaxPreLogonRsp : public EmapiSimpleRsp 
{
public:
	string * mAddress;
	int32 * mPort;
	int64 * mTicket;
	//int32 mMicroVersion;
	vector<const EmapiTaxConnectorEntry *> *mTaxConnectors;
	
	//void copy(const EmapiTaxPreLogonRsp &pObject);:0
	
	EmapiTaxPreLogonRsp();
	//EmapiTaxPreLogonRsp(const EmapiTaxPreLogonRsp &pObject);
	
	virtual ~EmapiTaxPreLogonRsp();

	//EmapiTaxPreLogonRsp & operator=(const EmapiTaxPreLogonRsp & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiTaxPreLogonRsp* clone() const;
};

class EmapiTaxLogonReq : public EmapiRequestMessage 
{
public:
	string * mMember;
	string * mUser;
	string * mPassword;
	int64 * mTicket;
	int32 * mPossDupSessId;
	int32 mMajorVersion;
	int32 mMinorVersion;
	int32 mMicroVersion;
	
	//void copy(const EmapiTaxLogonReq &pObject);
	
	EmapiTaxLogonReq();
	//EmapiTaxLogonReq(const EmapiTaxLogonReq &pObject);
	
	virtual ~EmapiTaxLogonReq();

	//EmapiTaxLogonReq & operator=(const EmapiTaxLogonReq & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiTaxLogonReq* clone() const;
};

class EmapiProteusRefDataMessage : public MessageDataIf
{
public:
	string * mKey;
	string * mCacheId;
	int32 * mAction;
	int64 mStateSequenceNumber;
	string * mUniqueObjectId;
	string * mTimeStamp;
	bool * mIsDeleted;

	string * mPmcSourceAddress;
	string * mPmcPartitionId;

	//void copy(const EmapiProteusRefDataMessage &pObject);:0
	
	EmapiProteusRefDataMessage();
	//EmapiProteusRefDataMessage(const EmapiProteusRefDataMessage &pObject);
	
	virtual ~EmapiProteusRefDataMessage();

	//EmapiProteusRefDataMessage & operator=(const EmapiProteusRefDataMessage & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiProteusRefDataMessage* clone() const;
};


class EmapiPublicMulticastAddress : public EmapiProteusRefDataMessage
{
public:
	string * mPmcAddress;
	int32 * mPmcPort;
	string * mPmcSourceAddress;
	string * mPmcPartitionId;

	//void copy(const EmapiPublicMulticastAddress &pObject);:0
	
	EmapiPublicMulticastAddress();
	//EmapiPublicMulticastAddress(const EmapiPublicMulticastAddress &pObject);
	
	virtual ~EmapiPublicMulticastAddress();

	//EmapiPublicMulticastAddress & operator=(const EmapiPublicMulticastAddress & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiPublicMulticastAddress* clone() const;
};


class EmapiPublicMulticastPartition : public EmapiProteusRefDataMessage
{
public:
	string * mPmcPartitionId;
	string * mPayloadContentType;
	int * mTimeToLive;
	int32 * mBundleSize;
	int32 * mHeartbeatInterval;
	string * mPmcContentId;
	vector<const EmapiPublicMulticastAddress *> *mPublicMulticastAddresses;
	
	//void copy(const EmapiPublicMulticastPartition &pObject);:0
	
	EmapiPublicMulticastPartition();
	//EmapiPublicMulticastPartition(const EmapiPublicMulticastPartition &pObject);
	
	virtual ~EmapiPublicMulticastPartition();

	//EmapiPublicMulticastPartition & operator=(const EmapiPublicMulticastPartition & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiPublicMulticastPartition* clone() const;
};


class EmapiPublicMulticastContent : public EmapiProteusRefDataMessage
{
public:
	string * mPmcContentId;
	string * mFlowIdList;
	string * mSubscriptionGroupList;
	vector<const EmapiPublicMulticastPartition *> *mPublicMulticastPartitions;
	
	//void copy(const EmapiPublicMulticastContent &pObject);:0
	
	EmapiPublicMulticastContent();
	//EmapiPublicMulticastContent(const EmapiPublicMulticastContent &pObject);
	
	virtual ~EmapiPublicMulticastContent();

	//EmapiPublicMulticastContent & operator=(const EmapiPublicMulticastContent & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiPublicMulticastContent* clone() const;
};


class EmapiTaxLogonRsp : public EmapiSimpleRsp 
{
public:
	bool * mLogonAccepted;
	int32 mLoginStatus;
	bool * mIsTestSystem;
	string * mSystemName;
	int32 * mPartitionHbtInterval;
	int32 * mClientHbtInterval;
	int32 * mMaxLostHeartbeats;
	vector<const EmapiPublicMulticastContent *> *mPublicMulticastContent;
	
	//void copy(const EmapiTaxLogonRsp &pObject);:0
	
	EmapiTaxLogonRsp();
	//EmapiTaxLogonRsp(const EmapiTaxLogonRsp &pObject);
	
	virtual ~EmapiTaxLogonRsp();

	//EmapiTaxLogonRsp & operator=(const EmapiTaxLogonRsp & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiTaxLogonRsp* clone() const;
};

class EmapiAbstractMeEvent : public MessageDataIf
{
public:
	int32 * mSubscriptionGroup;
	int64 mSequenceNumber;
	string * mTimeOfEvent;
	bool * mSequenceIndicator;

	//void copy(const EmapiAbstractMeEvent &pObject);
	
	EmapiAbstractMeEvent();
	//EmapiAbstractMeEvent(const EmapiAbstractMeEvent &pObject);
	
	virtual ~EmapiAbstractMeEvent();

	//EmapiAbstractMeEvent & operator=(const EmapiAbstractMeEvent & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiAbstractMeEvent* clone() const;
};


class EmapiHeartbeat : public EmapiAbstractMeEvent
{
public:
	string * mTimestamp;
	int32 * mPartition;
	
	//void copy(const EmapiHeartbeat &pObject);
	
	EmapiHeartbeat();
	//EmapiHeartbeat(const EmapiHeartbeat &pObject);
	
	virtual ~EmapiHeartbeat();

	//EmapiHeartbeat & operator=(const EmapiHeartbeat & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiHeartbeat* clone() const;
};


class EmapiHeartbeatReq : public EmapiRequestMessage 
{
public:
	string * mUserData;
	
	//void copy(const EmapiHeartbeatReq &pObject);
	
	EmapiHeartbeatReq();
	//EmapiHeartbeatReq(const EmapiHeartbeatReq &pObject);
	
	virtual ~EmapiHeartbeatReq();

	//EmapiHeartbeatReq & operator=(const EmapiHeartbeatReq & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiHeartbeatReq* clone() const;
};


class EmapiHeartbeatRsp : public EmapiSimpleRsp 
{
public:
	string * mTimestamp;
	string * mUserData;
	
	//void copy(const EmapiHeartbeatRsp &pObject);:0
	
	EmapiHeartbeatRsp();
	//EmapiHeartbeatRsp(const EmapiHeartbeatRsp &pObject);
	
	virtual ~EmapiHeartbeatRsp();

	//EmapiHeartbeatRsp & operator=(const EmapiHeartbeatRsp & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiHeartbeatRsp* clone() const;
};




class EmapiTaxConnectorEntry : public MessageDataIf 
{
public:

	int32 mIpPort;
	string * mIpAddress;
	int64 * mLoginTicket;
	vector<int32> *mSessionTypes;
	vector<int32> *mSubscriptionGroups;
	
	//void copy(const EmapiTaxConnectorEntry &pObject);
	
	EmapiTaxConnectorEntry();
	//EmapiTaxConnectorEntry(const EmapiTaxConnectorEntry &pObject);
	
	virtual ~EmapiTaxConnectorEntry();

	//EmapiTaxConnectorEntry & operator=(const EmapiTaxConnectorEntry & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	virtual const string to_string( string indent ) const;

	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiTaxConnectorEntry* clone() const;
};

}

#endif

