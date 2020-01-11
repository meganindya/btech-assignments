-- Anindya Kundu - 510817020

-- Create Table cust

create table cust (
	Cust_id varchar2(3),
	Lname varchar2(15),
	Fname varchar2(15),
	Area varchar2(2),
	Phone_no numeric(8)
);

-- Create Table movie

create table movie (
	Mv_no numeric(2),
	Title varchar(25),
	Type varchar(10),
	Star varchar(25),
	Price numeric(8,2)
);

-- Create Table invoice

create table invoice (
	Inv_no varchar2(3),
	Mv_no numeric(2),
	Cust_id varchar2(3),
	Issue_date date,
	Return_date date
);

-- Insert values into cust

insert into cust (
	Cust_id,
	Lname,
	Fname,
	Area,
	Phone_no
)
values (
	'101',
	'Verstappen',
	'Max',
	'RB',
	12345678
);

insert into cust (
	Cust_id,
	Lname,
	Fname,
	Area,
	Phone_no
)
values (
	'102',
	'Leclerc',
	'Charles',
	'FR',
	23456781
);

insert into cust (
	Cust_id,
	Lname,
	Fname,
	Area,
	Phone_no
)
values (
	'103',
	'Ricciardo',
	'Daniel',
	'RN',
	34567812
);

-- Create Table movie

insert into movie (
	Mv_no,
	Title,
	Type,
	Star,
	Price
)
values (
	1,
	'Hacksaw Ridge',
	'War',
	'Andrew Garfield',
	130
);

insert into movie (
	Mv_no,
	Title,
	Type,
	Star,
	Price
)
values (
	2,
	'Forrest Gump',
	'Biography',
	'Tom Hanks',
	150
);

insert into movie (
	Mv_no,
	Title,
	Type,
	Star,
	Price
)
values (
	3,
	'The Dark Knight',
	'Action',
	'Christian Bale',
	180
);

-- Create Table invoice

insert into invoice (
	Inv_no,
	Mv_no,
	Cust_id,
	Issue_date,
	Return_date
)
values (
	'M12',
	2,
	'102',
	'11-JUL-2019',
	'13-JUL-2019'
);

insert into invoice (
	Inv_no,
	Mv_no,
	Cust_id,
	Issue_date,
	Return_date
)
values (
	'M13',
	3,
	'102',
	'11-JUL-2019',
	'13-JUL-2019'
);

insert into invoice (
	Inv_no,
	Mv_no,
	Cust_id,
	Issue_date,
	Return_date
)
values (
	'M14',
	3,
	'101',
	'14-JUL-2019',
	'29-AUG-2019'
);

-- Queries

--1
select Fname, Lname from cust;

--2
select Type from movie;

--3
select * from cust where Phone_no > 5550000;

--4
select * from movie where Type = 'Action' or Type = 'Comedy';

--5
select * from movie where Price > 150 and Price < 200;

--6
select * from cust where Fname like '_a%';

--7
select Lname from cust where Lname like 's%' or Lname like 'f%';

--8
select * from cust where Area like '_a%';

--9
select * from cust where Area = 'da' or Area = 'mu' or Area = 'gh';

--10
select Mv_no, Title, Type from movie where Star like 'm%';

--11
select Title, Price * 15 as New_price from movie where Price > 150;

--12
select * from movie order by Title ASC;

--13
select Title, Type from movie where not Type = 'Horror';

--14
select Price / (Price - 100) as New_price from movie where Title = 'Home Alone';

--15
select Fname, Lname, Area, Cust_id from cust where Phone_no = null;

--16
select Fname, Lname from cust where Lname = null;

--17
select * from invoice where Issue_date like '%-SEP-%';

--18
select count(Cust_id) from cust;

--19
select sum(Price) from movie;

--20
select avg(Price) from movie;

--21
select max(Price) as max_price, min(Price) as min_price from movie;

--22
select count(Title) from movie where Price >= 150;

--23a
select 'The Invoice no. of Customer Id ' || Cust_id || ' is ' || Inv_no || ' and Movie no. is ' || Mv_no || '.' as Customer_Details from invoice;

--23b
select Cust_id || ' has taken Movie no. ' || Mv_no || ' on ' || Issue_date || ' and will return on ' || Return_date as Customer_Details from invoice;

--24
select Type, avg(Price) as Avg_Price from movie group by Type;

--25
select Type, count(Title) as Count from movie group by Type;

--26
select Type, count(Title) as Count from movie group by Type having Type = 'Comedy' or Type = 'Thriller';

--27
select Type, avg(Price) as Avg_Price from movie group by Type having avg(Price) <= 150;

--28
select Type, avg(Price) as Avg_Price from movie where Price >= 150 group by Type having Type = 'Comedy' or Type = 'Thriller';

--29
select Mv_no from invoice, cust where invoice.Cust_id = cust.Cust_id and cust.Fname = 'Ivan';

--30
select Fname, Lname, Mv_no from cust, invoice where invoice.Cust_id = cust.Cust_id;

--31
select Title, Cust_id, invoice.Mv_no from movie, invoice where invoice.Mv_no = movie.Mv_no;

--32
select Title, Type from movie, invoice, cust where cust.fname = 'Daniel' and cust.Cust_id = invoice.Cust_id and invoice.Mv_no = movie.Mv_no;

--33
select Fname, Lname from cust, movie, invoice where cust.Cust_id = invoice.Cust_id and invoice.Mv_no = movie.Mv_no and movie.Type = 'Biography';

--34
select 'The movie taken by ' || Fname || ' ' || Lname || ' is ' || Title || '.' as Movie_Details from cust, movie, invoice where invoice.Cust_id = cust.Cust_id and invoice.Mv_no = movie.Mv_no and movie.Mv_no >= 3;

--35
select Fname, Lname from cust where Cust_id in (select Cust_id from invoice where Mv_no = 1);

--36
select Fname, Lname, Area from cust where Cust_id = (select Cust_id from invoice where Inv_no = 'M14');

--37
select Title from movie where Mv_no in (select Mv_no from invoice where Cust_id in (select Cust_id from cust where Fname = 'Max' or Fname = 'Daniel'));

--38
select Type, Mv_no from movie where Mv_no in (select Mv_no from invoice where Cust_id = '101' or Cust_id = '102');

--39
select Cust_id from cust where Cust_id = (select Cust_id from invoice where Mv_no = (select Mv_no from movie where Star = 'Christian Bale'));

--40
select Fname, Lname, Phone_no from cust where Cust_id in (select Cust_id from invoice where extract(month from Issue_date) < 8);

--41
select Mv_no, Title from movie where Mv_no in (select Mv_no from invoice);

--42
select Inv_no, Issue_date from invoice;

--43
select to_char(Return_date, 'Month') as Return_date from invoice;

--44
select to_char(Issue_date, 'dd-Month-yy') as Issue_dates from invoice;

--45
select sysdate + 15 as New_date from dual;

--46
select floor(sysdate - Return_date) as Elapsed from dual, invoice;

--47
update cust set Phone_no = 56781234 where Fname = 'Lewis';

--48
update invoice set Issue_date = to_date('24/07/93', 'dd/mm/yy') where Cust_id = 101;

--49
delete from invoice where Inv_no = '104';

--50
delete from invoice where Return_date < to_date('10/07/93', 'dd/mm/yy');

--51
update invoice set Return_date = to_date('16-08-93', 'dd-mm-yy') where Inv_no = '104';