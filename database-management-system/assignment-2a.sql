-- Anindya Kundu - 510817020

-- Create Table Branch

create table Branch (
	B_name varchar2(10) PRIMARY KEY,
	City varchar2(10),
	CHECK(City IN('Delhi', 'Kolkata', 'Mumbai'))
);

-- Create Table Customer

create table Customer (
	C_name varchar2(10) PRIMARY KEY,
	City varchar2(10) NOT NULL,
	CHECK(C_name = UPPER(C_name))
);

-- Create Table Deposit

create table Deposit (
	Act_no varchar2(10) PRIMARY KEY,
	C_name varchar2(10),
	B_name varchar2(10),
	Amount numeric(8,2) NOT NULL,
	FOREIGN KEY(C_name) REFERENCES Customer(C_name),
	FOREIGN KEY(B_name) REFERENCES Branch(B_name)
);

-- Create Table Borrow

create table Borrow (
	Loan_no varchar2(10) PRIMARY KEY,
	C_name varchar2(10),
	B_name varchar2(10),
	Amount numeric(8,2),
	FOREIGN KEY(C_name) REFERENCES Customer(C_name),
	FOREIGN KEY(B_name) REFERENCES Branch(B_name),
	CHECK(Amount > 1000),
	CHECK(Loan_no = UPPER(Loan_no))
);

-- Insert values into Branch

insert into Branch (
	B_name,
	City
) values (
	'Hauz Khas',
	'Delhi'
);

insert into Branch (
	B_name,
	City
) values (
	'Chembur',
	'Mumbai'
);

insert into Branch (
	B_name,
	City
) values (
	'R K Puram',
	'Delhi'
);

insert into Branch (
	B_name,
	City
) values (
	'Jadavpur',
	'Kolkata'
);

-- Insert values into Customer

insert into Customer (
	C_name,
	City
) values (
	'ANJISHNU',
	'Mumbai'
);

insert into Customer (
	C_name,
	City
) values (
	'MAINAK',
	'Delhi'
);

insert into Customer (
	C_name,
	City
) values (
	'SHOUNAK',
	'Mumbai'
);

insert into Customer (
	C_name,
	City
) values (
	'MOYEEN',
	'Kolkata'
);

-- Insert values into Deposit

insert into Deposit (
	Act_no,
	C_name,
	B_name,
	Amount
) values (
	'BA1572',
	'SHOUNAK',
	'Jadavpur',
	10000
);

insert into Deposit (
	Act_no,
	C_name,
	B_name,
	Amount
) values (
	'DB2222',
	'ANJISHNU',
	'Chembur',
	15000
);

insert into Deposit (
	Act_no,
	C_name,
	B_name,
	Amount
) values (
	'AJ4675',
	'MAINAK',
	'Hauz Khas',
	6500
);

insert into Deposit (
	Act_no,
	C_name,
	B_name,
	Amount
) values (
	'RN7200',
	'MOYEEN',
	'Jadavpur',
	2000
);

-- Insert values into Borrow

insert into Borrow (
	Loan_no,
	C_name,
	B_name,
	Amount
) values (
	'SNS11',
	'MOYEEN',
	'R K Puram',
	5000
);

insert into Borrow (
	Loan_no,
	C_name,
	B_name,
	Amount
) values (
	'AFB26',
	'SHOUNAK',
	'R K Puram',
	2000
);

insert into Borrow (
	Loan_no,
	C_name,
	B_name,
	Amount
) values (
	'AFB28',
	'ANJISHNU',
	'Jadavpur',
	4500
);

insert into Borrow (
	Loan_no,
	C_name,
	B_name,
	Amount
) values (
	'TRR65',
	'MAINAK',
	'Hauz Khas',
	6550
);

-- Queries

--1
select Customer.C_name
from Deposit, Customer, Branch
where
	Deposit.C_name = Customer.C_name
	and Branch.B_name = Deposit.B_name
	and Customer.City = 'Mumbai'
	and Branch.City = 'Kolkata'
union
select Customer.C_name
from Borrow, Customer, Branch
where
	Borrow.C_name = Customer.C_name
	and Customer.City = 'Mumbai'
	and Branch.B_name = Borrow.B_name
	and Branch.City = 'Kolkata';

--2
select Customer.C_name
from Deposit, Customer, Branch
where
	Deposit.C_name = Customer.C_name
	and Deposit.B_name = Branch.B_name
	and Customer.City = Branch.City
union
select Customer.C_name
from Borrow, Customer, Branch
where
	Borrow.C_name = Customer.C_name
	and Borrow.B_name = Branch.B_name
	and Customer.City = Branch.City;

--3
select distinct C_name
from Deposit, Branch
where
	Deposit.B_name = Branch.B_name
	and Branch.City = (
		select City
		from Deposit, Branch
		where
			C_name = 'SHOUNAK'
			and Deposit.B_name = Branch.B_name)
	and not C_name = 'SHOUNAK';

--4
select Act_no, C_name, Deposit.B_name, Amount
from Deposit, Branch
where
	Deposit.B_name = Branch.B_name
	and Branch.City = (
		select City
		from Customer
		where C_name = 'SHOUNAK')
union
select Loan_no, C_name, Borrow.B_name, Amount
from Borrow, Branch
where
	Borrow.B_name = Branch.B_name
	and Branch.City = (
		select City
		from Customer
		where C_name = 'SHOUNAK');

--5
select count(Deposit.C_name)
from Deposit, Borrow
where Deposit.C_name = Borrow.C_name;

--6
select C_name
from Borrow
where
	Amount > (
		select Amount
		from Borrow
		where C_name = 'ANJISHNU');

--7
select Deposit.C_name
from Deposit, Branch, (
	select distinct Branch.City
	from Branch, Deposit, Borrow
	where
		(Deposit.C_name = 'SHOUNAK'
		and Deposit.B_name = Branch.B_name)
		or
		(Borrow.C_name = 'SHOUNAK'
		and Borrow.B_name = Branch.B_name))
	Scity
where Deposit.B_name = Branch.B_name
and Branch.City = Scity.City
and Branch.City = (
	select City
	from Customer
	where C_name = 'MOYEEN');

--8
select Customer.C_name
from Deposit, Customer, (
		select Deposit.C_name
		from Deposit, Branch
		where
			Deposit.B_name = Branch.B_name
			and Branch.City = 'Delhi'
		union
		select Borrow.C_name
		from Borrow, Branch
		where
			Borrow.B_name = Branch.B_name
			and Branch.City = 'Delhi'
	) Nname
where
	Deposit.C_name = Customer.C_name
	and Customer.City = 'Kolkata'
	and Customer.C_name = Nname.C_name;

--9
select Customer.C_name
from Customer, (
		select City
		from Customer
		where C_name = 'SHOUNAK'
	) Ncity, (
		select C_name
		from Borrow
		union
		select C_name
		from Deposit
	) Nnames
where
	Customer.City = Ncity.City
	and Customer.C_name = Nnames.C_name
	and not Customer.C_name = 'SHOUNAK';

--10
select distinct Customer.C_name
from Customer, (
		select City
		from Borrow, Branch
		where
			(C_name = 'SHOUNAK'
			and Borrow.B_name = Branch.B_name)
		union
		select City
		from Deposit, Branch
		where
			(C_name = 'SHOUNAK'
			and Deposit.B_name = Branch.B_name)
	) Ncity, (
		select C_name
		from Borrow
		union
		select C_name
		from Deposit
	) Nnames, (
		select C_name, City
		from Borrow, Branch
		where
			Borrow.B_name = Branch.B_name
		union
		select C_name, City
		from Deposit, Branch
		where
			Deposit.B_name = Branch.B_name
	) Ccity
where
	Customer.City = 'Kolkata'
	and Customer.C_name = Nnames.C_name
	and Ccity.City = Ncity.City
	and Customer.C_name = Nnames.C_name
	and not Customer.C_name = 'SHOUNAK';

--11
select distinct City
from Borrow, Branch
where
	Borrow.B_name = Branch.B_name
	and
		C_name = 'SHOUNAK'
		or C_name = 'MAINAK';
union
select distinct City
from Deposit, Branch
where
	Deposit.B_name = Branch.B_name
	and
		C_name = 'SHOUNAK'
		or C_name = 'MAINAK';

--12
select B_name
from (
		select max(C_no) as C_max
		from (
				select B_name, count(B_name) as C_no
				from Deposit
				group by B_name
			) Bcnt
	) Cm, (
			select B_name, count(B_name) as C_no
			from Deposit
			group by B_name
	) Bc
where
	Cm.C_max = Bc.C_no;

--13
select C_name
from (
		select max(A_no) as A_max
		from (
				select C_name, max(Amount) as A_no
				from Deposit
				group by C_name
			) Bcnt
	) Cm, (
			select C_name, max(Amount) as A_no
			from Deposit
			group by C_name
	) Bc
where
	Cm.A_max = Bc.A_no;

--14
select Customer.C_name, Amt
from Customer, (
		select C_name, sum(Amount) as Amt
		from Deposit
		group by C_name
		union
		select C_name, sum(Amount) as Amt
		from Borrow
		group by C_name
	) Nname
where
	Nname.C_name = Customer.C_name
	and City = 'Delhi';

--15
select Deposit.C_name
from Deposit, (
		select B_name
		from Borrow
		where
			C_name = 'ANJISHNU'
		union
		select B_name
		from Deposit
		where
			C_name = 'ANJISHNU'
	) Brch
where
	Deposit.B_name = Brch.B_name
	and not Deposit.C_name = 'ANJISHNU';

--16
select sum(Amount)
from Customer, (
		select City
		from Customer
		where
			C_name = 'SHOUNAK'
	) Csh, Deposit
where
	Customer.City = Csh.City
	and Deposit.C_name = Customer.C_name;

--17
select C_name
from Deposit
where
	B_name = 'Jadavpur'
	and Amount = (
		select max(Amount)
		from Deposit
		where B_name = 'Jadavpur'
		group by B_name
	);

--18
select C_name
from Deposit
where
	Amount = (
		select max(Amount)
		from Deposit, (
				select B_name
				from Branch
				where
					Branch.City in (
						select City
						from Branch, Deposit
						where
							Branch.B_name = Deposit.B_name
							and C_name = 'SHOUNAK'
						union
						select City
						from Branch, Borrow
						where
							Branch.B_name = Borrow.B_name
							and C_name = 'SHOUNAK'
					)
			) Sbrch
		where
			Deposit.B_name in Sbrch.B_name
	);

--19
select Deposit.C_name
from Deposit, Customer
where
	Customer.C_name = Deposit.C_name
	and Customer.city = 'Delhi'
intersect (
		select C_name
		from Deposit
		where B_name = 'Hauz Khas'
		union
		select C_name
		from Borrow
		where B_name = 'Hauz Khas'
	);

--20
select depBr, dep_cnt, brw_cnt
from (
		select B_name as depBr, count(distinct(C_name)) as dep_cnt
		from Deposit
		group by B_name
	), (
		select B_name as brwBr, count(distinct(C_name)) as brw_cnt
		from Borrow
		group by B_name
	)
where
	depBr = brwBr
	and dep_cnt > brw_cnt;

--21
select req_city, C_name
from borrow, (
		select req_city, max(amt) as Max_Borrow
		from (
			select C_name, amount as amt, city as req_city
			from Borrow, Branch
			where Branch.b_name = Borrow.b_name
		)
		group by req_city
	)
where borrow.amount = Max_Borrow;

--22
update Deposit
set Amount = Amount * 1.1
where C_name in (
	select Deposit.C_name
	from Deposit, Customer, Branch
	where
		Deposit.B_name = Branch.B_name
		and Customer.C_name = Deposit.C_name
		and Customer.City = 'Kolkata'
		and Customer.C_name in (
			select C_name
			from Deposit, Branch
			where
				Deposit.B_name = Branch.B_name
				and Branch.city = 'Delhi'
			union
			select C_name
			from Borrow, Branch
			where
				Borrow.B_name = Branch.B_name
				and Branch.City = 'Delhi'
		)
	);

--23
update Deposit
set Amount = (
		select max(Amount)
		from Deposit
		where B_name = 'Jadavpur'
	)
where C_name = 'MAINAK';

--24
update Deposit
set Amount = Amount - 1000
where
	C_name = 'ANJISHNU'
	and B_name in (
		select B_name
		from Deposit
		where C_name = 'MAINAK'
	);

update Deposit
set Amount = Amount + 1000
where
	C_name = 'MAINAK'
	and b_name in (
		select B_name
		from Deposit
		where C_name = 'ANJISHNU'
	);

--25
update Deposit
set Amount = Amount + 1000
where
	C_name in (
		select C_name
		from Deposit
		where Amount = (
			select max(Amount)
			from Deposit
			group by B_name
		)
	);

--26
update Deposit
set Amount = Amount + 1000
where C_name in (
	select C_name
	from Deposit
	group by B_name
	where 

--27
delete from Borrow
where B_name in (
	select B_name
	from Borrow
	group by B_name
	having avg(Amount) < 1000
);

--28
delete from Borrow
where B_name in (
	select B_name
	from Borrow
	group by B_name
	having count(C_name) = (
		select min(count(C_name))
		from Borrow
		group by B_name
	)
);

--29
delete from Deposit
where C_name in (
	select C_name
	from Customer
	where
		C_name in ('SHOUNAK', 'MAINAK')
		and City = (
			select City
			from Customer
			where C_name = 'SHOUNAK'
		)
		and City = (
			select City
			from Customer
			where c_name='MAINAK')
	);