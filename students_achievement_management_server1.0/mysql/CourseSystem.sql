-- 创建数据库
create database if not exists CourseSystem;
use CourseSystem;

-- 创建表
create table if not exists TableStudent(
    ID    char(12) not null primary key,
    Name  char(20) not null,
    Sex   char(8)  not null,
    Class char(10) not null,
    DateOfBirth char(8) not null);

-- 创建用户并授权
grant select, insert, update on TableStudent to student@'localhost';
grant select, update on TableStudent to teacher@'localhost';
