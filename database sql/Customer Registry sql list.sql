-- SQL file used to recreate the database for the application.
-- Used with SQL Server 2019 and Microsofts db management studio for the project
-- By itself does not work, would require opening up firewall for sql server and tinkering with sql server config.


CREATE DATABASE CustomerRegistry
GO

USE CustomerRegistry  
GO  

create table dbo.Customers (
cid int PRIMARY KEY NOT NULL identity(1,1),
FirstName char(30),
LastName char(30),
EmailAddress char(50) NOT NULL UNIQUE,
PhoneNumber char(20) NOT NULL UNIQUE,
DateJoined datetime NOT NULL,
);
GO

CREATE PROCEDURE spInsert_Customer @FirstName char(30), @LastName char(30), @EmailAddress char(50), @PhoneNumber char(20)
	AS
	BEGIN
	-- Insert customer detail from parameters
	INSERT INTO dbo.Customers (FirstName,LastName,EmailAddress,PhoneNumber, DateJoined)
		VALUES (@FirstName,@LastName,@EmailAddress,@PhoneNumber, CURRENT_TIMESTAMP)
	END
GO

CREATE PROCEDURE spView_Customer @EmailAddress char(50)
	AS
	BEGIN
	-- View customer detail by checking with email address
	SELECT FirstName, LastName, PhoneNumber FROM dbo.Customers
		WHERE EmailAddress = @EmailAddress
	END
GO

CREATE PROCEDURE spUpdate_Customer @FirstName char(30), @LastName char(30), @EmailAddress char(50), @PhoneNumber char(20)
	AS
	BEGIN
	-- Update customer detail from with parameters, check with email address
	UPDATE dbo.Customers
		SET FirstName = @FirstName,
			LastName = @LastName,
			PhoneNumber = @PhoneNumber
		WHERE
			EmailAddress = @EmailAddress
	END
GO

INSERT INTO dbo.Customers (FirstName,LastName,EmailAddress,PhoneNumber,DateJoined)
	VALUES ('luke', 'kokorick', 'lukekoko@myloco.com', '07484848484', CURRENT_TIMESTAMP)
GO

SELECT * FROM dbo.Customers
GO

UPDATE dbo.Customers  
    SET FirstName = 'name changed'  
    WHERE cid = 1  
GO  

EXECUTE spInsert_Customer 'luke', 'kokorick', 'lukekokfo@myloco.com', '074848484845'
GO

EXECUTE spView_Customer 'lukekokfo@myloco.com'
GO

EXECUTE spUpdate_Customer 'updated', 'updated', 'lukekokfo@myloco.com', '074848484845'
GO