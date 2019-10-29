Postgre SQL's SQL for HOP
==========================

### Creation of tables.

    CREATE TABLE account(
      id             SERIAL PRIMARY KEY,
      custId         VARCHAR (10) UNIQUE NOT NULL,
      username       VARCHAR (50) UNIQUE NOT NULL,
      fullname       VARCHAR (50) NOT NULL,
      password       VARCHAR (50) NOT NULL,
      nickname       VARCHAR (20) DEFAULT 'Me',
      email          VARCHAR (355) UNIQUE,
      role           VARCHAR (10) NOT NULL,
      verified       BOOLEAN DEFAULT 0,
      enabled        BOOLEAN DEFAULT 0, 
      createdOn      TIMESTAMP NOT NULL,
      modifiedOn     TIMESTAMP NOT NULL,
      lastLogin      TIMESTAMP
    );

    CREATE TABLE contact (
      id             SERIAL PRIMARY KEY,
      accountId      INTEGER,                     
      country        VARCHAR (50),
      state          VARCHAR (50),
      pincode        VARCHAR (10),
      address        VARCHAR (150),
      mobile1        VARCHAR (15),
      verified1      BOOLEAN DEFAULT 0,
      mobile2        VARCHAR (15),
      verified2      BOOLEAN DEFAULT 0,

      lattitude      FLOAT,
      longitude      FLOAT,

      createdOn      TIMESTAMP NOT NULL,
      modifiedOn     TIMESTAMP NOT NULL,


      CONSTRAINT contact_accountId_fkey FOREIGN KEY (accountId)
         REFERENCES account (id) MATCH SIMPLE
         ON UPDATE NO ACTION ON DELETE NO ACTION,
    );

    CREATE TABLE location (
      id            SERIAL PRIMARY KEY,
      accountId     INTEGER,
      lattitude     FLOAT,
      longitude     FLOAT,
     
      createdOn     TIMESTAMP NOT NULL,

      CONSTRAINT location_accountId_fkey FOREIGN KEY (accountId)
        REFERENCES account (id) MATCH SIMPLE
        ON UPDATE NO ACTION ON DELETE NO ACTION,
    );

    create table hop (
      id            SERIAL PRIMARY KEY,
      accountId     INTEGER,

      messageId     INTEGER,
      actionId      INTEGER,
      locationId    INTEGER,

      nextHop       TIMESTAMP,
      expiresOn     TIMESTAMP,

      enabled       BOOLEAN DEFAULT 1,

      createdOn     TIMESTAMP,
      modifiedOn    TIMESTAMP,
    );



References
------------------
* [http://www.postgresqltutorial.com/][1]


[1]: http://www.postgresqltutorial.com/
