create table if not exists registerinfo(
    id int not null primary key,
    mailaddr char(40),
    passwd char(16));

grant select, update on coursesystem.registerinfo to \
student@localhost identified by 'student123';
