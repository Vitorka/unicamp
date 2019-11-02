-- -----------------------------------------------------
-- Giovani Nascimento Pereira - RA: 168609
-- Matheus Campanha Ferreira - RA: 174435
-- Vitor Kaoru Aoki - RA: 178474
-- -----------------------------------------------------

-- MySQL Workbench Forward Engineering
-- drop database mydb;
SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Drops
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Produto_has_Aditivo` ;
DROP TABLE IF EXISTS `mydb`.`Produto_has_Ingrediente` ;
DROP TABLE IF EXISTS `mydb`.`Produto_has_Categoria` ;
DROP TABLE IF EXISTS `mydb`.`Produto_has_LocalVenda` ;
DROP TABLE IF EXISTS `mydb`.`InformacoesNutricionais` ;
DROP TABLE IF EXISTS `mydb`.`Aditivo` ;
DROP TABLE IF EXISTS `mydb`.`Ingrediente` ;
DROP TABLE IF EXISTS `mydb`.`Produto` ;
DROP TABLE IF EXISTS `mydb`.`Embalagem` ;
DROP TABLE IF EXISTS `mydb`.`LocalVenda` ;
DROP TABLE IF EXISTS `mydb`.`Categoria` ;

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Categoria`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Categoria` (
  `CategoriaProduto` VARCHAR(100),
  `idCategoria` INT NOT NULL,
  PRIMARY KEY (`idCategoria`))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`LocalVenda`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`LocalVenda` (
  `LocalVenda` VARCHAR(100) NULL,
  `idLocal` INT NOT NULL,
  PRIMARY KEY (`idLocal`))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Embalagem`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Embalagem` (
  `TipoEmbalagem` VARCHAR(100),
  `MaterialEmbalagem` VARCHAR(100),
  PRIMARY KEY (`TipoEmbalagem`, `MaterialEmbalagem`))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Produto`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Produto` (
  `idProduto` INT NOT NULL,
  `NomeProduto` VARCHAR(100),
  `Quantidade` VARCHAR(100),
  `Marca` VARCHAR(100),
  `LocalOrigem` VARCHAR(100),
  `Embalagem_TipoEmbalagem` VARCHAR(100),
  PRIMARY KEY (`idProduto`),
  INDEX `fk_Produto_Embalagem1_idx` (`Embalagem_TipoEmbalagem` ASC),
  CONSTRAINT `fk_Produto_Embalagem1`
    FOREIGN KEY (`Embalagem_TipoEmbalagem`)
    REFERENCES `mydb`.`Embalagem` (`TipoEmbalagem`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Ingrediente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Ingrediente` (
  `NomeIngrediente` VARCHAR(100) NULL,
  `idIngrediente` INT NOT NULL,
  PRIMARY KEY (`idIngrediente`))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Aditivo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Aditivo` (
  `NomeAditivo` VARCHAR(100) NULL,
  `idAditivo` INT NOT NULL,
  PRIMARY KEY (`idAditivo`))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`InformacoesNutricionais`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`InformacoesNutricionais` (
  `Produto_idProduto` INT NOT NULL,
  `Energia` DECIMAL(50),
  `Gordura` DECIMAL(50),
  `GorduraSaturada` DECIMAL(50),
  `Carboidratos` DECIMAL(50),
  `Acucar` DECIMAL(50),
  `Proteinas` DECIMAL(50),
  `Sal` DECIMAL(50),
  `Sodio` DECIMAL(50),
  INDEX `fk_InformacoesNutricionais_Produto1_idx` (`Produto_idProduto` ASC),
  PRIMARY KEY (`Produto_idProduto`),
  CONSTRAINT `fk_InformacoesNutricionais_Produto1`
    FOREIGN KEY (`Produto_idProduto`)
    REFERENCES `mydb`.`Produto` (`idProduto`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Produto_has_LocalVenda`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Produto_has_LocalVenda` (
  `Produto_idProduto` INT NOT NULL,
  `LocalVenda_idLocal` INT NOT NULL,
  PRIMARY KEY (`Produto_idProduto`, `LocalVenda_idLocal`),
  INDEX `fk_Produto_has_LocalVenda_LocalVenda1_idx` (`LocalVenda_idLocal` ASC),
  INDEX `fk_Produto_has_LocalVenda_Produto1_idx` (`Produto_idProduto` ASC),
  CONSTRAINT `fk_Produto_has_LocalVenda_Produto1`
    FOREIGN KEY (`Produto_idProduto`)
    REFERENCES `mydb`.`Produto` (`idProduto`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Produto_has_LocalVenda_LocalVenda1`
    FOREIGN KEY (`LocalVenda_idLocal`)
    REFERENCES `mydb`.`LocalVenda` (`idLocal`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Produto_has_Categoria`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Produto_has_Categoria` (
  `Produto_idProduto` INT NOT NULL,
  `Categoria_idCategoria` INT NOT NULL,
  PRIMARY KEY (`Produto_idProduto`, `Categoria_idCategoria`),
  INDEX `fk_Produto_has_Categoria_Categoria1_idx` (`Categoria_idCategoria` ASC),
  INDEX `fk_Produto_has_Categoria_Produto1_idx` (`Produto_idProduto` ASC),
  CONSTRAINT `fk_Produto_has_Categoria_Produto1`
    FOREIGN KEY (`Produto_idProduto`)
    REFERENCES `mydb`.`Produto` (`idProduto`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Produto_has_Categoria_Categoria1`
    FOREIGN KEY (`Categoria_idCategoria`)
    REFERENCES `mydb`.`Categoria` (`idCategoria`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Produto_has_Ingrediente`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Produto_has_Ingrediente` (
  `Produto_idProduto` INT NOT NULL,
  `Ingrediente_idIngrediente` INT NOT NULL,
  PRIMARY KEY (`Produto_idProduto`, `Ingrediente_idIngrediente`),
  INDEX `fk_Produto_has_Ingrediente_Ingrediente1_idx` (`Ingrediente_idIngrediente` ASC),
  INDEX `fk_Produto_has_Ingrediente_Produto1_idx` (`Produto_idProduto` ASC),
  CONSTRAINT `fk_Produto_has_Ingrediente_Produto1`
    FOREIGN KEY (`Produto_idProduto`)
    REFERENCES `mydb`.`Produto` (`idProduto`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Produto_has_Ingrediente_Ingrediente1`
    FOREIGN KEY (`Ingrediente_idIngrediente`)
    REFERENCES `mydb`.`Ingrediente` (`idIngrediente`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`Produto_has_Aditivo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Produto_has_Aditivo` (
  `Produto_idProduto` INT NOT NULL,
  `Aditivo_idAditivo` INT NOT NULL,
  PRIMARY KEY (`Produto_idProduto`, `Aditivo_idAditivo`),
  INDEX `fk_Produto_has_Aditivo_Aditivo1_idx` (`Aditivo_idAditivo` ASC),
  INDEX `fk_Produto_has_Aditivo_Produto1_idx` (`Produto_idProduto` ASC),
  CONSTRAINT `fk_Produto_has_Aditivo_Produto1`
    FOREIGN KEY (`Produto_idProduto`)
    REFERENCES `mydb`.`Produto` (`idProduto`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Produto_has_Aditivo_Aditivo1`
    FOREIGN KEY (`Aditivo_idAditivo`)
    REFERENCES `mydb`.`Aditivo` (`idAditivo`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Populando o banco
-- -----------------------------------------------------

-- Tabela Embalagem
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaEmbalagem.csv'
INTO TABLE Embalagem
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(TipoEmbalagem, MaterialEmbalagem);


-- Tabela Produto
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaProduto.csv'
INTO TABLE Produto
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(idProduto, NomeProduto, Quantidade, Marca, LocalOrigem, Embalagem_TipoEmbalagem);

-- Tabela Ingrediente
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaIngrediente.csv'
INTO TABLE Ingrediente
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(NomeIngrediente, idIngrediente);

-- Tabela Produto_has_Ingrediente
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaProdutoHasIngrediente.csv'
INTO TABLE Produto_has_Ingrediente
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(Produto_idProduto, Ingrediente_idIngrediente);

-- Tabela Categoria
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaCategoria.csv'
INTO TABLE Categoria
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(CategoriaProduto, idCategoria);

-- Tabela Produto_Has_Categoria
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaProdutoHasCategoria.csv'
INTO TABLE Produto_has_Categoria
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(Produto_idProduto, Categoria_idCategoria);

-- Tabela Aditivo
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaAditivo.csv'
INTO TABLE Aditivo
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(NomeAditivo, idAditivo);

-- Tabela Produto_has_Aditivo
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaProdutoHasAditivo.csv'
INTO TABLE Produto_has_Aditivo
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(Produto_idProduto, Aditivo_idAditivo);

-- Tabela InformacoesNutricionais
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaInformacoesNutricionais.csv'
INTO TABLE InformacoesNutricionais
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(Produto_idProduto, Energia, Gordura, GorduraSaturada, Carboidratos, Acucar, Proteinas, Sal, Sodio);

-- Tabela LocalVenda
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaLocalVenda.csv'
INTO TABLE LocalVenda
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(LocalVenda, idLocal);

-- Tabela Produto_has_LocalVenda
LOAD DATA LOCAL INFILE '/home/vaoki/ec/mc536/Projeto/TabelaProdutoHasLocalVenda.csv'
INTO TABLE Produto_has_LocalVenda
CHARACTER SET utf8
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(Produto_idProduto, LocalVenda_idLocal);

-- -----------------------------------------------------
-- Consultas
-- -----------------------------------------------------

-- Retorna uma tabela com o valor energético medio dos produtos, agrupados por categorias
select C.CategoriaProduto as Categoria, 
	   avg(T2.Energia) as QtdEnergia
	   from  Categoria C
			 inner join (
                   select PC.*
                   from Produto_has_Categoria PC) T1
                   on C.idCategoria = T1.Categoria_idCategoria
             inner join (
				   select INut.Energia, INut.Produto_idProduto 
                   from InformacoesNutricionais INut) T2
                   on T2.Produto_idProduto = T1.Produto_idProduto
        group by Categoria;     
            
-- Retorna uma tabela ordenada pela quantidade de sodio, dos produtos que são vendidos no Reino Unido
select T2.NomeProduto, 
	   T3.Sodio as QtdSodio
       from LocalVenda l
		    inner join (
				  select PL.*
                  from Produto_has_LocalVenda PL) T1
                  on l.idLocal = T1.LocalVenda_idLocal
		    inner join (
				  select p.idProduto,
                  p.NomeProduto
                  from Produto p) T2
                  on T1.Produto_idProduto = T2.idProduto
            inner join (
                  select INut.Sodio,
                  INut.Produto_idProduto
                  from InformacoesNutricionais INut) T3
                  on T1.Produto_idProduto = T3.Produto_idProduto
        where l.LocalVenda = 'United Kingdom'         
		order by QtdSodio;
        
-- Retorna uma tabela ordenada pela media de carboidratos e acucares de um produto, agrupado por categorias
select C.CategoriaProduto as Categoria,
	   AVG(T2.Carboidratos) as QtdCarboidratos,
       AVG(T2.Acucar) as QtdAcucar
       from Categoria C
			inner join (
                  select PC.* 
                  from Produto_has_Categoria PC) T1
                  on T1.Categoria_idCategoria = C.idCategoria
			inner join (
				  select INut.Carboidratos,
						 INut.Acucar,
                         INut.Produto_idProduto
                         from InformacoesNutricionais INut) T2
                         on T2.Produto_idProduto = T1.Produto_idProduto
        group by C.CategoriaProduto, T2.Carboidratos, T2.Acucar
        order by T2.Carboidratos, T2.Acucar;

-- Retorna uma tabela com a Embalagem de todos os produtos com menos de 100g de proteínas em sua composição        
select p.Embalagem_TipoEmbalagem as Embalagem,
       T1.Proteinas as QtdProteinas
	   from Produto p
			inner join (
				  select INut.Produto_idProduto,
                         INut.Proteinas
                         from InformacoesNutricionais INut) T1
                         on p.idProduto = T1.Produto_idProduto and T1.Proteinas < 100
        where p.Embalagem_TipoEmbalagem is not null and trim(p.Embalagem_TipoEmbalagem) != ""
        group by p.Embalagem_TipoEmbalagem, T1.Proteinas
        order by T1.Proteinas;                        

-- Retorna uma tabela com a quantidade de aditivos que existem por produtos de determinada categoria
select c.CategoriaProduto as Categoria,
       count(T2.Produto_idProduto) as QtdAditivos
       from Categoria c
            inner join (
                  select PC.*
                  from Produto_has_Categoria PC) T1
                  on c.idCategoria = T1.Categoria_idCategoria
            inner join (  
				  select a.Produto_idProduto
                         from Produto_has_Aditivo a) T2
				  on T1.Produto_idProduto = T2.Produto_idProduto
        group by c.CategoriaProduto   
        order by QtdAditivos;

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
