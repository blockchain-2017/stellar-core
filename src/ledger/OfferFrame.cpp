// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the ISC License. See the COPYING file at the top-level directory of
// this distribution or at http://opensource.org/licenses/ISC

#include "ledger/OfferFrame.h"
#include "database/Database.h"

using namespace std;

namespace stellar
{
    const char *OfferFrame::kSQLCreateStatement = "CREATE TABLE IF NOT EXISTS Offers (						\
			accountID		CHARACTER(35),		\
			sequence		INT UNSIGNED,		\
			takerPaysCurrency Blob(20),			\
			takerPaysIssuer CHARACTER(35),		\
			takerGetsCurrency Blob(20),			\
			takerGetsIssuer CHARACTER(35),		\
			amount BIGINT UNSIGNED,	\
			price BIGINT UNSIGNED,	\
			BOOL passive						\
	);";

    OfferFrame::OfferFrame()
    {

    }
    OfferFrame::OfferFrame(const LedgerEntry& from) : EntryFrame(from)
    {

    }

    void OfferFrame::from(const Transaction& tx) 
    {
        mEntry.type(OFFER);
        mEntry.offer().accountID = tx.account;
        mEntry.offer().amount = tx.body.createOfferTx().amount;
        mEntry.offer().price = tx.body.createOfferTx().price;
        mEntry.offer().sequence = tx.body.createOfferTx().sequence;
        mEntry.offer().takerGets = tx.body.createOfferTx().takerGets;
        mEntry.offer().takerPays = tx.body.createOfferTx().takerPays;
        mEntry.offer().passive = tx.body.createOfferTx().passive;
    }

    void OfferFrame::calculateIndex()
    {
        // TODO.2
    }

    

    void OfferFrame::storeDelete(Json::Value& txResult, LedgerMaster& ledgerMaster)
    {

    }
    void OfferFrame::storeChange(EntryFrame::pointer startFrom, Json::Value& txResult, LedgerMaster& ledgerMaster)
    {

    }
    void OfferFrame::storeAdd(Json::Value& txResult, LedgerMaster& ledgerMaster)
    {

    }

    void OfferFrame::dropAll(Database &db)
    {
        db.getSession() << "DROP TABLE IF EXISTS Offers;";
        db.getSession() << kSQLCreateStatement;
    }

    /* 
    


	OfferEntry::OfferEntry(SLE::pointer sle)
	{
		mAccountID = sle->getFieldAccount160(sfAccount);
		mSequence = sle->getFieldU32(sfSequence);

		mTakerPays=sle->getFieldAmount(sfTakerPays);
		mTakerGets = sle->getFieldAmount(sfTakerGets);
		
		if(sle->isFieldPresent(sfExpiration))
			mExpiration = sle->getFieldU32(sfExpiration);
		else mExpiration = 0;  

		uint32_t flags = sle->getFlags();
		
		mPassive = flags & lsfPassive;  
 	}

	void OfferEntry::calculateIndex()
	{
		Serializer  s(26);

		s.add16(spaceOffer);       //  2
		s.add160(mAccountID);      // 20
		s.add32(mSequence);        //  4

		mIndex= s.getSHA512Half();
	}

	void OfferEntry::insertIntoDB()
	{
		//make sure it isn't already in DB
		deleteFromDB();

		
		uint160 paysIssuer = mTakerPays.getIssuer();
		uint160 getsIssuer = mTakerGets.getIssuer();

		string sql = str(boost::format("INSERT INTO Offers (accountID,sequence,takerPaysCurrency,takerPaysAmount,takerPaysIssuer,takerGetsCurrency,takerGetsAmount,takerGetsIssuer,expiration,passive) values ('%s',%d,x'%s',%d,'%s',x'%s',%d,'%s',%d,%d);")
			% mAccountID.base58Encode(RippleAddress::VER_ACCOUNT_ID)
			% mSequence
			% to_string(mTakerPays.getCurrency())
            % mTakerPays.getText()
			% paysIssuer.base58Encode(RippleAddress::VER_ACCOUNT_ID)
			% to_string(mTakerGets.getCurrency())
			% mTakerGets.getText()
			% getsIssuer.base58Encode(RippleAddress::VER_ACCOUNT_ID)
			% mExpiration
			% mPassive);

		{
			DeprecatedScopedLock sl(getApp().getLedgerDB()->getDBLock());
			Database* db = getApp().getLedgerDB()->getDB();

			if(!db->executeSQL(sql, true))
			{
				CLOG(WARNING, ripple::Ledger) << "SQL failed: " << sql;
			}
		}
	}
	void OfferEntry::updateInDB()
	{
		uint160 paysIssuer = mTakerPays.getIssuer();
		uint160 getsIssuer = mTakerGets.getIssuer();

		string sql = str(boost::format("UPDATE Offers set takerPaysCurrency=x'%s', takerPaysAmount=%d, takerPaysIssuer='%s', takerGetsCurrency=x'%s' ,takerGetsAmount=%d, takerGetsIssuer='%s' ,expiration=%d, passive=%d where accountID='%s' AND sequence=%d;")	
			% to_string(mTakerPays.getCurrency())
			% mTakerPays.getText()
			% paysIssuer.base58Encode(RippleAddress::VER_ACCOUNT_ID)
			% to_string(mTakerGets.getCurrency())
			% mTakerGets.getText()
			% getsIssuer.base58Encode(RippleAddress::VER_ACCOUNT_ID)
			% mExpiration
			% mPassive
			% mAccountID.base58Encode(RippleAddress::VER_ACCOUNT_ID)
			% mSequence);

		{
			DeprecatedScopedLock sl(getApp().getLedgerDB()->getDBLock());
			Database* db = getApp().getLedgerDB()->getDB();

			if(!db->executeSQL(sql, true))
			{
				CLOG(WARNING, ripple::Ledger) << "SQL failed: " << sql;
			}
		}
	}
	void OfferEntry::deleteFromDB()
	{
		string sql = str(boost::format("DELETE FROM Offers where accountID='%s' AND sequence=%d;")
			% mAccountID.base58Encode(RippleAddress::VER_ACCOUNT_ID)
			% mSequence);

		{
			DeprecatedScopedLock sl(getApp().getLedgerDB()->getDBLock());
			Database* db = getApp().getLedgerDB()->getDB();

			if(!db->executeSQL(sql, true))
			{
				CLOG(WARNING, ripple::Ledger) << "SQL failed: " << sql;
			}
		}
	}

   
    */
}