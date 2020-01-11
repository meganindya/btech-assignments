create table student (
	stdID numeric(4) PRIMARY KEY,
	stdName varchar2(20),
	markEng numeric(3),
	markMat numeric(3),
	markPhy numeric(3),
	check (markEng >= 0 and markEng <= 100),
	check (markMat >= 0 and markMat <= 100),
	check (markPhy >= 0 and markPhy <= 100)
);

insert into student values (
	1002, 'Shounak', 80, 75, 50
);

insert into student values (
	1003, 'Mainak', 59, 89, 92
);

insert into student values (
	1001, 'Arijit', 77, 10, 81
);

insert into student values (
	1005, 'Sourya', 66, 97, 80
);

insert into student values (
	1004, 'Ankit', 25, 50, 70
);


--1
create view examRes as
select stdID, markEng, markMat, markPhy
from student;

--insert
insert into examRes values (
	1006, 79, 84, 68
);

--update
update examRes
set markMat = 75
where
	stdID = 1001;

--delete
delete from examRes
where markMat = 75;


--2
create table contact (
	stdID numeric(4) PRIMARY KEY,
	phone numeric(10),
	city varchar2(10)
);

insert into contact values (
	1003, 9876543210, 'Kolkata'
);

insert into contact values (
	1005, 9876543210, 'Raiganj'
);

insert into contact values (
	1004, 9463125558, 'Kohima'
);

insert into contact values (
	1006, 9653214852, 'Srinagar'
);


create view newStd as
select student.stdID, stdName, phone, city
from student, contact
where student.stdId = contact.stdID;

--insert
insert into newStd values (
	1001, 'Árijit', 0123456789, 'Garia'
);

--update
update newStd
set stdName = 'Shounak'
where
	stdID = 1006;

--delete
delete from newStd
where city = 'Kohima';