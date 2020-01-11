-- Anindya Kundu - 510817020

create table emp(
	eno	 varchar2(4),
	name varchar2(10),
	dno	 varchar2(4),
	sal  number(8,2),
	loc	 varchar2(10)
);

insert into emp values('E01', 'ANKIT',	 'D01', 8000, 'Kolkata');
insert into emp values('E02', 'SHOUNAK', 'D03', 5000, 'Kolkata');
insert into emp values('E03', 'ARIJIT',  'D02', 6000, 'Mumbai');
insert into emp values('E04', 'MOYEEN',  'D02', 3000, 'Kolkata');
insert into emp values('E05', 'MAINAK',  'D03', 7500, 'Delhi');
insert into emp values('E06', 'KUNAL',	 'D01', 4000, 'Chennai');

select * from emp;

set serveroutput on;


--1
declare
	cursor c is select sal from emp;
	sal_temp emp.sal % type;
	sal_high emp.sal % type;
	cnt	number := 0;
begin
	open c;
	
	loop
		fetch c into sal_temp;
		select max(sal) into sal_high from emp;
		
		if sal_high = sal_temp then
			delete from emp
			where sal = sal_temp;
			cnt := cnt + 1;
		end if;
		
		if cnt = 2 then
			exit;
		end if;
	end loop;
	
	if c % ISOPEN then
		close c;
	end if;
end;
/

--1
declare
	cursor c is
		select eno
		from emp
		order by sal desc;
	enum emp.eno % type;
	i integer;
begin
	open c;
	
	for i in 1 .. 2 loop
		fetch c into enum;
		
		delete from emp
		where eno = enum;
	end loop;
	
	if c % ISOPEN then
		close c;
	end if;
end;
/

--2
declare
	row_temp emp % rowtype; 
	cursor c is
		select eno, name, sal, loc
		from emp
		where loc = 'Kolkata';
	cnt number := 0;
	val number;
begin
	open c;
	
	loop 
		fetch c into row_temp;
		exit when c % NOTFOUND;
		
		val := row_temp.sal;
		val := val * 1.15;
		
		update emp
		set sal = val
		where eno = row_temp.eno;
		cnt := cnt + 1;
	end loop;
	
	if cnt > 0 then
		dbms_output.put_line('Salary updated for ' || cnt || ' employees');
	else
  		dbms_output.Put_line('No employee from Kolkata');
	end if;
	
	if c % ISOPEN then
		close c;
	end if;
end;
/


create table account (
	act_no varchar2(8),
	age	   numeric(3),
	amount numeric(8, 2)
);

insert into account values('ACT01', 57, 5000);
insert into account values('ACT02', 62, 2000);
insert into account values('ACT03', 65, 8000);
insert into account values('ACT04', 49, 4500);
insert into account values('ACT05', 61, 3700);
insert into account values('ACT06', 68, 9100);

select * from account;


--3 a
declare
	act_1 account.act_no % type := '&act_1';
	act_2 account.act_no % type := '&act_2';
	cursor c is
		select act_no
		from account;
	ano account.act_no % type;
	amt account.amount % type;
begin
	open c;
	
	loop
		fetch c into ano;
		exit when c % NOTFOUND;
		
		if ano = act_1 then
			select amount into amt from account where act_no = ano;
			
			if amt > 1999 then
				update account
				set amount = amount - 2000
				where act_no = act_1;
				
				update account
				set amount = amount + 2000
				where act_no = act_2;
				
				dbms_output.put_line('Transfer completed successfully');
			else
				dbms_output.put_line('Insufficient amount');  	
		    end if;
		end if;
	end loop;
	
	if c % ISOPEN then
		close c;
	end if;
end;
/

--3 b
declare
	cursor c is
		select act_no
		from account
		where age > 60;
	ano account.act_no % type;
begin
	open c;
	
	for i in 1 .. 3 loop
		fetch c into ano;
		exit when c % NOTFOUND;
		
		update account
		set amount = amount * 1.05
		where act_no = ano;
	end loop;
	
	if c % ISOPEN then
		close c;
	end if;
end;
/

--4
declare
	cursor c is select * from emp;
	emp_temp emp % rowtype;
	sal_temp emp.sal % type;
	eno_temp emp.eno % type;
	cnt number;
begin
	insert into emp values('E07', 'ROHAN', 'D02', 5000, 'Mumbai');
	
	open c;
	
	loop
		fetch c into emp_temp; 
		exit when c % NOTFOUND;
		
		sal_temp := emp_temp.sal;
		sal_temp := sal_temp + 2000;
		
		if (sal_temp > 20000) then
			sal_temp := sal_temp - 2000;
			update emp set sal = sal_temp where eno = emp_temp.eno;
		end if;
	end loop;
	
	if c % ISOPEN
		close c;
	end if;
end;
/

--5
declare
	cursor c is select * from emp;
	emp_temp emp % rowtype;
	flag number := 0;
	dno_temp emp.dno % type := '&dno_temp';
	invalid_dept_exception exception;
begin
	open c;
	
	loop
		fetch c into emp_temp;
		exit when c % NOTFOUND;
		
		if dno_temp = emp_temp.dno then
			flag := 1;
			dbms_output.put_line('The salary of employee ' || emp_temp.eno || ' is ' || emp_temp.sal);
		end if;
	end loop;
	
	if flag = 0 then
		raise invalid_dept_exception;
	end if;
exception
	when invalid_dept_exception then
		dbms_output.put_line('Invalid department no');
end;
/

--6
create table product (
	pno				varchar2(4),
	pname			varchar2(16),
	actual_price	number(8, 2),
	sale_price		number(8, 2)
);

insert into product values('P01', 'ABC', 100, 120);
insert into product values('P02', 'BCD', 120, 130);
insert into product values('P03', 'CDE', 100, 90);
insert into product values('P04', 'DEF', 100, 100);
insert into product values('P05', 'EFG', 130, 220);

select * from product;


declare
	cursor c is select * from product;
	row_temp product % rowtype;
	pnum product.pno % type := '&pnum';
	flag integer := 0;
	profit number(4, 2);
	invalid_product_no exception;
	profit_zero exception;
begin
	open c;
	
	loop
		fetch c into row_temp;
		exit when c % NOTFOUND;
		
		if row_temp.pno = pnum then
			flag := 1;
			profit := row_temp.sale_price - row_temp.actual_price;
      
			if profit > 0 then
				dbms_output.put_line('Profit on product ' || pnum || ' is ' || profit);
			end if;
			
			if profit <= 0 then
				raise profit_zero;
			end if;
		end if;
	end loop;
	
	if flag = 0 then
		raise invalid_product_no;
	end if;
	
	if c % ISOPEN then
		close c;
	end if;
exception
	when invalid_product_no then
		dbms_output.put_line('Invalid product number');
	when profit_zero then
		dbms_output.put_line('Zero profit');
end;
/