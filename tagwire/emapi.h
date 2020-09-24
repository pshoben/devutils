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

namespace emapi
{
	class EmapiTaxConnectorEntry;
	class EmapiTaxPreLogonReq;
	class EmapiTaxPreLogonRsp;
		
	static const int EmapiMessageType_EmapiOrderInsertReq = 1;
	static const int EmapiMessageType_EmapiOrderUpdateReq = 8;
	static const int EmapiMessageType_EmapiOrderCancelReq = 6;

	static const int EmapiMessageType_EmapiOrderInsertRsp = 2;
	static const int EmapiMessageType_EmapiOrderUpdateRsp = 9;
	static const int EmapiMessageType_EmapiOrderCancelRsp = 7;

	static const int EmapiMessageType_EmapiTaxConnectorEntry = 68;

	static const int EmapiMessageType_EmapiTaxPreLogonReq = 66;
	static const int EmapiMessageType_EmapiTaxPreLogonRsp = 67;
	
	static const int EmapiMessageType_EmapiRequestMessage = 237;

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
	int32 mMicroVersion;
	vector<const EmapiTaxConnectorEntry *> *mTaxConnectors;
	
	//void copy(const EmapiTaxPreLogonRsp &pObject);
	
	EmapiTaxPreLogonRsp();
	//EmapiTaxPreLogonRsp(const EmapiTaxPreLogonRsp &pObject);
	
	virtual ~EmapiTaxPreLogonRsp();

	//EmapiTaxPreLogonRsp & operator=(const EmapiTaxPreLogonRsp & pObject);

	virtual void pack(TagwireEncoder& pEncode) const;
	virtual void unpack(TagwireDecoder& pDecode);
	virtual const int getClassId() const;
	virtual const string getMessageName() const;	
	const int getMessageType() const;	
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiTaxPreLogonRsp* clone() const;
};



class EmapiTaxConnectorEntry : public MessageDataIf 
{
public:

	int32 * mIpPort;
	string * mIpAddress;
	int64 * mLoginTicket;
	int32 mMicroVersion;
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
	//const string toString() const;
	//void traceMessage(MessageTrace *pTrace, int pLevel) const;
	//virtual EmapiTaxConnectorEntry* clone() const;
};

}

#endif

