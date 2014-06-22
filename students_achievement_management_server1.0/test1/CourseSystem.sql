-- 创建数据库
create database if not exists course_system;
use course_system;

-- 创建表
/*teacher*/
create table if not exists teacher(
    id    int      not null primary key,
    name  char(20) not null,
    sex   char(8)  not null,
    phone char(15),
    title char(20) not null,
    department char(100),
    birthday char(8));

/*student*/
create table if not exists student(
    id    int      not null primary key,
    name  char(20) not null,
    sex   char(8)  not null,
    class char(10) not null,
    birthday char(8));
    
/*course*/
create table if not exists course(
    id    int      not null primary key,
    name  char(20) not null,
    credit int     not null,
    course_hours int not null,
    tid    int   not null,
    course_type char(20));
    
/*select_course*/
create table if not exists select_course(
    cid   int      not null,
    sid   int      not null);
    
/*homework*/
create table if not exists homework(
    id    int      auto_increment  primary key,
    name  char(20) not null,
    arrange_time   char(8)  not null,
    cid   int      not null);

/*do_homework*/
create table if not exists do_homework(
    sid   int      not null,
    hid   int      not null,
    hname char(20) not null,
    score int      not null);
    
    
-- 创建用户并授权
/*grant select, insert, update on TableStudent to student@'localhost';
  grant select, update on TableStudent to teacher@'localhost';
*/
