/*
 *Giovani Nascimento Pereira - RA: 168609
 *Matheus Campanha Ferreira - RA: 17443
 *Vitor Kaoru Aoki - RA: 178474
 */

import java.sql.*;

public class Buscas {
	
	/* Busca1: Retorna uma tabela com o valor energético medio dos produtos, 
	 * agrupados por categorias
	 */
	public void Busca1 (Connection conexao) {
		try {
			Statement comando = conexao.createStatement();
			String stringComando = "select C.CategoriaProduto as Categoria, \n" + 
					"	   avg(T2.Energia) as QtdEnergia\n" + 
					"	   from  Categoria C\n" + 
					"			 inner join (\n" + 
					"                   select PC.*\n" + 
					"                   from Produto_has_Categoria PC) T1\n" + 
					"                   on C.idCategoria = T1.Categoria_idCategoria\n" + 
					"             inner join (\n" + 
					"				   select INut.Energia, INut.Produto_idProduto \n" + 
					"                   from InformacoesNutricionais INut) T2\n" + 
					"                   on T2.Produto_idProduto = T1.Produto_idProduto\n" + 
					"        group by Categoria;  ";
			ResultSet resultado = comando.executeQuery(stringComando);
			
			while(resultado.next()) {
				String categoria = resultado.getString("Categoria");
				double energia = resultado.getDouble("QtdEnergia");
				System.out.println("---------------------------------------------------------------");
				System.out.println("Categoria: " + categoria);
				System.out.println("Quantidade Energia: " + energia);
				System.out.println("---------------------------------------------------------------");
			}
			
			resultado.close();
			comando.close();
			
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	/* Busca2: Retorna uma tabela ordenada pela quantidade de sodio, 
	 * dos produtos que são vendidos no pais escolhido
	 */
	public void Busca2 (Connection conexao, String pais) {
		try {
			String stringComando = "select T2.NomeProduto, \n" +
					"	   T3.Sodio as QtdSodio\n" +
					"       from LocalVenda l\n" +
					"		    inner join (\n" +
					"				  select PL.*\n" +
					"                  from Produto_has_LocalVenda PL) T1\n" +
					"                  on l.idLocal = T1.LocalVenda_idLocal\n" +
					"		    inner join (\n" +
					"				  select p.idProduto,\n" +
					"                  p.NomeProduto\n" +
					"                  from Produto p) T2\n" +
					"                  on T1.Produto_idProduto = T2.idProduto\n" +
					"            inner join (\n" +
					"                  select INut.Sodio,\n" +
					"                  INut.Produto_idProduto\n" +
					"                  from InformacoesNutricionais INut) T3\n" +
					"                  on T1.Produto_idProduto = T3.Produto_idProduto\n" +
					"        where l.LocalVenda = ?         \n" +
					"		order by QtdSodio;";
			PreparedStatement comando = conexao.prepareStatement(stringComando);
			comando.setString(1, pais);
			ResultSet resultado = comando.executeQuery();
			
			while(resultado.next()) {
				String nomeProduto = resultado.getString("T2.NomeProduto");
				double qtdSodio = resultado.getDouble("QtdSodio");
				System.out.println("---------------------------------------------------------------------------");
				System.out.println("Nome do Produto: " + nomeProduto);
				System.out.println("Quantidade Sodio: " + qtdSodio);
				System.out.println("---------------------------------------------------------------------------");
			}
			
			resultado.close();
			comando.close();

		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	/* Busca3: Retorna uma tabela ordenada pela media de carboidratos e acucares de um produto, 
	 * agrupado por categorias
	 */
	public void Busca3 (Connection conexao) {
		try {
			Statement comando = conexao.createStatement();
			String stringComando = "select C.CategoriaProduto as Categoria,\n" + 
					"	   AVG(T2.Carboidratos) as QtdCarboidratos,\n" +
					"       AVG(T2.Acucar) as QtdAcucar\n" + 
					"       from Categoria C\n" + 
					"			inner join (\n" + 
					"                  select PC.* \n" + 
					"                  from Produto_has_Categoria PC) T1\n" + 
					"                  on T1.Categoria_idCategoria = C.idCategoria\n" + 
					"			inner join (\n" + 
					"				  select INut.Carboidratos,\n" + 
					"						 INut.Acucar,\n" + 
					"                         INut.Produto_idProduto\n" + 
					"                         from InformacoesNutricionais INut) T2\n" + 
					"                         on T2.Produto_idProduto = T1.Produto_idProduto\n" + 
					"        group by C.CategoriaProduto, T2.Carboidratos, T2.Acucar\n" + 
					"        order by T2.Carboidratos, T2.Acucar;";
			ResultSet resultado = comando.executeQuery(stringComando);
			
			while(resultado.next()) {
				String categoria = resultado.getString("Categoria");
				double qtdCarboidratos = resultado.getDouble("QtdCarboidratos");
				double qtdAcucar = resultado.getDouble("QtdAcucar");
				System.out.println("---------------------------------------------------------------");
				System.out.println("Categoria: " + categoria);
				System.out.println("Quantidade Carboidratos: " + qtdCarboidratos);
				System.out.println("Quantidade Acucar: " + qtdAcucar);
				System.out.println("---------------------------------------------------------------");
			}
			
			resultado.close();
			comando.close();
			
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	/* Busca4: Retorna uma tabela com a Embalagem de todos os produtos com menos, da quantidade escolhida, de
	 * proteínas em sua composição 
	 */
	public void Busca4 (Connection conexao, double qtdProt) {
		try {

			String stringComando = "select p.Embalagem_TipoEmbalagem as Embalagem,\n" + 
					"       T1.Proteinas as QtdProteinas\n" + 
					"	   from Produto p\n" + 
					"			inner join (\n" + 
					"				  select INut.Produto_idProduto,\n" + 
					"                         INut.Proteinas\n" + 
					"                         from InformacoesNutricionais INut) T1\n" + 
					"                         on p.idProduto = T1.Produto_idProduto and T1.Proteinas < ?\n" +
					"        where p.Embalagem_TipoEmbalagem is not null and trim(p.Embalagem_TipoEmbalagem) != \"\"\n" + 
					"        group by p.Embalagem_TipoEmbalagem, T1.Proteinas\n" + 
					"        order by T1.Proteinas;";
			PreparedStatement comando = conexao.prepareStatement(stringComando);
			comando.setDouble(1, qtdProt);
			ResultSet resultado = comando.executeQuery();

			while(resultado.next()) {
				String embalagem = resultado.getString("Embalagem");
				double qtdProteinas = resultado.getDouble("QtdProteinas");
				System.out.println("---------------------------------------------------------------");
				System.out.println("Emabalagem: " + embalagem);
				System.out.println("Quantidade Proteinas: " + qtdProteinas);
				System.out.println("---------------------------------------------------------------");
			}
			
			resultado.close();
			comando.close();
			
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	/* Busca5: Retorna uma tabela com a quantidade de aditivos que existem por produtos de determinada categoria
	 */
	public void Busca5 (Connection conexao) {
		try {
			Statement comando = conexao.createStatement();
			String stringComando = "select c.CategoriaProduto as Categoria,\n" + 
					"       count(T2.Produto_idProduto) as QtdAditivos\n" + 
					"       from Categoria c\n" + 
					"            inner join (\n" + 
					"                  select PC.*\n" + 
					"                  from Produto_has_Categoria PC) T1\n" + 
					"                  on c.idCategoria = T1.Categoria_idCategoria\n" + 
					"            inner join (  \n" + 
					"				  select a.Produto_idProduto\n" + 
					"                         from Produto_has_Aditivo a) T2\n" + 
					"				  on T1.Produto_idProduto = T2.Produto_idProduto\n" + 
					"        group by c.CategoriaProduto   \n" + 
					"        order by QtdAditivos;";
			ResultSet resultado = comando.executeQuery(stringComando);
			
			while(resultado.next()) {
				String categoria = resultado.getString("Categoria");
				double qtdAditivos = resultado.getDouble("QtdAditivos");
				System.out.println("---------------------------------------------------------------");
				System.out.println("Categoria: " + categoria);
				System.out.println("Quantidade Aditivos: " + qtdAditivos);
				System.out.println("---------------------------------------------------------------");
			}
			
			resultado.close();
			comando.close();

		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
}
