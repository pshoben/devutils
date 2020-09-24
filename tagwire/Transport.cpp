

int tcpipRead( int socketNum, void * pBuffer, int pSizeToRead )
{
	int tSize;
	int tBytesRead = 0;
	char * tBuffer = (char *0 tBuffer;
	if (socketNum<0) return TPS_SESSION_CLOSED;

	while( tBytesRead < pSizeToRead ) 
	{
		tSize = recv( socketNum, &tBuffer[ tBytesRead ] , pSizeToRead - tBytesRead, 0 );
		if (tSize == 0)
			return TPS_SESSION_CLOSED;
		else
			if (tSize <0)
				return tSize;
			else
				tBytesRead += tSize;
	}
	return TPS_READ_OK;
}

