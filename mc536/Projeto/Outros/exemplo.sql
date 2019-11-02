-- drop database mydb;
create schema agenda_enderecos;
use agenda_enderecos;
drop table if exists dadosagenda;
create table if not exists dadosagenda (
Registro integer,
Nome varchar(50),
Endereco varchar(50),
Bairro varchar(40),
Cidade varchar(40),
Estado char(2),
CEP char(9),
Telefone varchar(20) NULL,
primary key(Registro));
insert into dadosagenda (Registro,Nome,Endereco, Bairro,Cidade,Estado,CEP, Telefone)
values (1,"Mario Sergio Roberto", "Av. 1, 1200", "Centro", "Rio Claro", "SP","13500000","19 9900-0099");
insert into dadosagenda (Registro,Nome,Endereco, Bairro,Cidade,Estado,CEP, Telefone)
values (2,"Jose Augusto Jorge", "R.XV de Novembro, 500", "Jd. Amélia", "São Paulo", "SP","03000-100","11
0011-0011");
insert into dadosagenda (Registro,Nome,Endereco, Bairro,Cidade,Estado,CEP, Telefone)
values (3,"Adolfo José Carlos", "R.Nove de Julho, 800", "Vila Nova", "Atibaia", "SP","12900-000","11 4000-5000");