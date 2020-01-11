-- Anindya Kundu - 510817020

--1
declare
	year number := 2016;
begin
	if	mod(year, 4) = 0
		and mod(year, 100) != 0
		or mod(year, 400) = 0 then
		dbms_output.put_line(year || ' is a leap year ');
	else
		dbms_output.put_line(year || ' is not a leap year.');
	end if;
end;
/

--2
declare
	numorg 	integer := 1221;
	numrev 	integer := 0;
	temp 	integer;
begin
	temp := numorg;
	
	while temp > 0 loop
		numrev := numrev * 10 + mod(temp, 10);
		temp := floor(temp / 10);
	end loop;
	
	if	numorg = numrev then
		dbms_output.put_line(numorg || ' is a palindrome');
	else
		dbms_output.put_line(numorg || ' is not a palindrome');
	end if;
end;
/

--3
declare
	numorg 	integer := 153;
	numnew 	integer := 0;
	temp 	integer;
begin
	temp := numorg;
	
	while temp > 0 loop
		numnew := numnew + power(mod(temp, 10), 3);
		temp := floor(temp / 10);
	end loop;	
	
	if	numorg = numnew then
		dbms_output.put_line(numnew || ' is an armstrong number');
	else
		dbms_output.put_line(numnew || ' is not an armstrong number');
	end if;
end;
/

--4
declare
	num1 integer := 14;
	num2 integer := 35;
	num3 integer := 84;
	tem1 integer;
	tem2 integer;
	tem3 integer;
	temp integer;
begin
	tem1 := num1;
	tem2 := num2;
	tem3 := num3;

	while mod(tem2, tem1) != 0 loop
		temp := mod(tem2, tem1);
		
		tem2 := tem1;
		tem1 := temp;
	end loop;
	
	while mod(tem3, tem1) != 0 loop
		temp := mod(tem3, tem1);
		
		tem3 := tem1;
		tem1 := temp;
	end loop;
	
	dbms_output.put_line('GCD of ' || num1 ||
		', ' || num2 || ', and ' || num3 || ' is ' || tem1);
end;
/

--5
declare
	num1 integer := 2;
	num2 integer := 4;
	num3 integer := 6;
	tem1 integer;
	tem2 integer;
	tem3 integer;
	temp integer;
	lcm1 integer;
begin
	tem1 := num1;
	tem2 := num2;
	tem3 := num3;

	while mod(tem2, tem1) != 0 loop
		temp := mod(tem2, tem1);
		
		tem2 := tem1;
		tem1 := temp;
	end loop;
	
	lcm1 := (num1 * num2) / tem1;
	
	while mod(tem3, tem1) != 0 loop
		temp := mod(tem3, tem1);
		
		tem3 := tem1;
		tem1 := temp;
	end loop;
	
	tem1 := (lcm1 * num3) / tem1;
	
	dbms_output.put_line('LCM of ' || num1 ||
		', ' || num2 || ', and ' || num3 || ' is ' || tem1);
end;
/

--6
declare
	num		integer := 28;
	sumfac	integer := 1;
	i		integer;
begin
	for i in 2 .. (num - 1) loop
		if (mod(num, i) = 0) then
			sumfac := sumfac + i;
		end if;
	end loop;
	
	if sumfac = num and num != 1 then
		dbms_output.put_line(num || ' is a perfect number.');
	else
		dbms_output.put_line(num || ' is not a perfect number.');
	end if;
end;
/

--7
declare
	string	varchar2(16) := 'thequickfox';
	countV	integer := 0;
	countC	integer := 0;
	i		integer := 0;
	c		character;
begin
	for i in 1 .. length(string) loop
		c := substr(string, i, 1);
		
		if c = 'a' or c = 'e' or c = 'i' or c = 'o' or c = 'u' then
			countV := countV + 1;
		else
			countC := countC + 1;
		end if;
	end loop;
	
	dbms_output.put_line('For the string ' || string);
	dbms_output.put_line('Vowels: ' || countV || ', Consonants: ' || countC);
end;
/

--8
declare
	actNum varchar2(6);
	actAmt integer;
begin
	actNum := '&actNum';
	
	select amount
	into actAmt
	from deposit
	where Act_no = actNum;
	
	if actAmt >= 5000 then
		dbms_output.Put_line('Amount is ' || actAmt);
	else
		actAmt := actAmt + 2000;
		dbms_output.Put_line('New amount is ' || actAmt);
	end if;
	
	update deposit
	set amount = actAmt
	where Act_no = actNum;
end;
/

--9
create table emp(
	eno	 varchar2(4),
	name varchar2(10),
	sal  number(8,2)	
);

insert into emp values('E01', 'ANKIT', 8000);
insert into emp values('E02', 'SHOUNAK', 5000);
insert into emp values('E03', 'ARIJIT', 6000);
insert into emp values('E04', 'MOYEEN', 300000);
insert into emp values('E05', 'MAINAK', 7500);
insert into emp values('E06', 'KUNAL', 40000);

select * from emp;

declare
	e_id	varchar2(4);
	e_name	varchar2(10);
begin
	e_id := &e_id;
	
	select name
	into e_name
	from emp
	where eno = 'e_id';
	
	dbms_output.put_line('Hi ' || e_id || ' - ' || e_name);
	
	exception
	when NO_DATA_FOUND then
		dbms_output.put_line(e_id || ' does not exist');
end;
/

declare
	e_id	varchar2(4);
	e_name	varchar2(10);
	e_sal	number(8,2); 
	cnt		number := 0;
begin
	e_id := '&e_id';
	
	select count(*)
	into cnt
	from emp
	where eno = e_id;
	
	if cnt = 0 then
		e_name	:= '&e_name';
		e_sal	:= &e_sal;
		dbms_output.put_line(e_id || ' added');
	else
		dbms_output.put_line('Duplicate ID');
	end if;
end;
/

--10
declare
	bname	varchar2(16);
	cnt		number;
begin
	bname := '&bname';
	
	select count(b_name)
	into cnt
	from borrow
	where B_name = bname;
	
	if cnt > 0 then
		delete from borrow
		where B_name = bname;
		
		dbms_output.put_line(cnt || ' rows have been deleted');
	else
		dbms_output.put_line('No entries in branch ' || bname);
	end if;
end;
/