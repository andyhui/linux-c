create table if not exists registerinfo(
    id int not null primary key,
    mailaddr char(60),
    passwd char(16));

grant insert, select, update, delete on course_system.registerinfo to \
admin@localhost identified by 'admin123';

grant select, update on course_system.registerinfo to \
teacher@localhost identified by 'teacher123';

grant select, update on course_system.registerinfo to \
student@localhost identified by 'student123';
