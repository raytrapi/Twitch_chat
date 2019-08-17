create table estados(
   id int not null,
   nombre varchar(200) not null,
   primary key (id)
) CHARACTER SET = utf8;
create table usuarios(
   id int not null auto_increment,
   nombre varchar(100) not null,
   avatar varchar(300) null,
   color varchar(10) null,
   primary key (id),
   unique key (nombre)
) character set = utf8;
create table mensajes(
   id int not null auto_increment,
   fecha timestamp not null default CURRENT_TIMESTAMP,
   idEstado int not null,
   idUsuario int not null,
   mensaje varchar(500) not null,
   primary key (id),
   foreign key fk_mensajes_estados (idEstado) references estados(id),
   foreign key fk_mensajes_usuarios (idUsuario) references usuarios(id)
) character set = utf8;

insert into estados values(1, "Registrado"); -- Cuando se da de alta
insert into estados values(2, "Procesado"); -- Una vez procesado por los diferentes sistemas que tengamos de control
insert into estados values(3, "Rechazado"); -- Si está rechazado
insert into estados values(4, "Aceptado"); -- Aceptado