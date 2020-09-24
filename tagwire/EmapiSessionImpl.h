#ifndef EmapiSessionImpl_H
#define EmapiSessionImpl_H

#include <cstdarg>
#include <memory>
#include <cstdio>

#include "MessageQueueItems.h"
#include "LockManager.h"
#include "EmapiHeader.h"
#include "UserHandleContainer.h"
#include "CallbackcDelivery.h"
#include "Thread.h"
//#include "HeartbeatGenerator.h"
#include "EmapiTagwireWrapper.h"

using std::string;

namespace emapi {

enum EmapiSessionState { INITIALIZED, CONNECTED, CLOSING, CLOSED };

class EmapiSession;

class EmapiSessionImpl : public ThreadExecutable
{
// friend class HeartbeatGenerator;
private:
	volatile int mRefCount;
	EmapiSession * 	mEmapiSession;
	int		mSessionId;
	int		mLogLevel;
	volatile enum	EmapiSessionState mState;
	int		mSocket;
//	Lock		mMutex;
//	Event		mThreadStartEv;
//	std::auto_ptr<LockManager>	mLockManager;
//	std::auto_ptr<MsgRequestContainer>	mRqstContainer;
//	std::auto_ptr<CallbackDelivery>		mCallbackTask;
//	std::auto_ptr<UserHandleContainer>	mUsrHandleContainer;

	string	mSessionUser;
	string	mSessionTax;
	int	mSessionPort;
	string	mSessionConnectTime;
	int	mDeliveryQueueLength_100;
	int	mSendTimeoutMS;
	int	mConnectTimeoutMS;
	Thread	mConnectionHandler;
//	std::auto_ptr<HeartbeatGenerator>	mHeartbeatGenerator;
	volatile int32	mLogoutRefId;
	static bool	preLoginCalled;

	int connect( const string & pTaxGateway, int pPort );

public:
//	EmapiSessionImpl( EmapiSession *pEmapiSession,
			

	

	
#endif
