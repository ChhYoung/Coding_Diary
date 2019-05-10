# TSQL编程

### 1. TSQL编程实现判断变量是字母，数字还是其他字符，并输出其类型。 

```sql
-- 通过 if 语句求一个字符是是什么类型
declare @ch char
set @ch = '#'
if UPPER(@ch)>='A' and UPPER(@ch)<='Z' 
	print @ch+'是字母'
else if @ch>='0' and @ch<='9'
	print @ch+'是数字'
else 
	print @ch+'是其他字符'
	
-- 通过 case 语句判断
declare @ch2 char
set @char2 = 'A'
print 
case
	when UPPER(@ch2)>='A' and UPPER(@ch2)<='Z' then @ch2+'是字母'
	when @ch2>='0' and @ch2<='9' then @ch2+'是数字'
	else @ch2+'是其他字符'
end
```

### 2. TSQL编程实现输出所有3000以内能被17整除的数

```sql
declare @result table(Num int null)
declare @i int 
set @i = @i + 1
while @i <= 3000
begin 
	if ( @i % 17 )=0
		insert into @result  values(@i)
	set @i = @i + 1
end
select *
from @result
```

### 3.编程实现函数，通过辗转相除法解两个正整数的最大公约数。

```sql
CREATE  FUNCTION GetGys    
    (    
      @num1 BIGINT ,    
      @num2 BIGINT    
    )    
RETURNS BIGINT    
AS    
    BEGIN    
        DECLARE @m BIGINT;    
        DECLARE @i BIGINT;    
        IF ( @num1 < @num2 )--确保@num1永远是大的 @num2永远是小的    
            BEGIN     
                SET @m = @num2;     
                SET @num2 = @num1;    
                SET @num1 = @m;     
            END;     
        SET @i = @num1 % @num2;    
        WHILE @i > 0    
            BEGIN     
                SELECT  @num1 = @num2 ,    
                        @num2 = @i ,    
                        @i = @num1 % @num2;    
            END;     
        RETURN @num2;    
    END;    
GO   
select dbo.GetGys(18,24) as 最大公约数
```

**触发器**



