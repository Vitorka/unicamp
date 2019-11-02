/*
 *Giovani Nascimento Pereira - RA: 168609
 *Matheus Campanha Ferreira - RA: 17443
 *Vitor Kaoru Aoki - RA: 178474
 */

import java.sql.*;
import java.util.Scanner;
import java.util.Vector;

public class ConexaoMysql {

	public static void main(String[] args) {
		
		Buscas buscas = new Buscas();
		String nomeBanco = "jdbc:mysql://localhost:3306/mydb";
		String nomeUsuario = "root";
		String senhaBanco = "vka-2715-06";
		Connection conexao;

		boolean menu = true;
		Scanner scan = new Scanner(System.in);
		String sair;
		int busca;

		try {
			Class.forName("com.mysql.jdbc.Driver");
			conexao = DriverManager.getConnection(nomeBanco, nomeUsuario, senhaBanco);

			while(menu) {

				System.out.println("Escolha uma das Buscas:");
				System.out.println("[1] Retorna uma tabela com o valor energético medio dos produtos, agrupados " +
						           "por categorias");
				System.out.println("[2] Retorna uma tabela ordenada pela quantidade de sodio, dos produtos que " +
						           "são vendidos no pais escolhido");
				System.out.println("[3] Retorna uma tabela ordenada pela media de carboidratos e acucares " +
								   "de um produto, agrupado por categorias");
				System.out.println("[4] Retorna uma tabela com a Embalagem de todos os produtos com menos, da " +
						           "quantidade escolhida, de proteínas em sua composição ");
				System.out.println("[5] Retorna uma tabela com a quantidade de aditivos que existem por produtos " +
						           "de determinada categoria");
				busca = Integer.parseInt(scan.nextLine());

				switch (busca) {

					case 1:
						buscas.Busca1(conexao);
						break;
					case 2:
						Vector paises = new Vector();
						inicializapaises(paises);
						System.out.println("\nFavor escolher (atraves do respectivo numero) um dos paises listados abaixo:");
						System.out.println("[1] United Kingdom\n[2] Canada\n[3] France\n[4] Germany\n" +
										   "[5] Italy\n[6] Romania\n[7] Spain\n[8] Australia\n[9] Belgium\n" +
								           "[10] Netherlands\n[11] United States\n[12] Switzerland\n");
						int id;
						id = Integer.parseInt(scan.nextLine());
						buscas.Busca2(conexao, (String) paises.get(id - 1));
						break;
					case 3:
						buscas.Busca3(conexao);
						break;
					case 4:
						System.out.println("\nFavor inserir uma quantidade de proteinas entre [0, 100]:");
						double qtdProteinas;
						qtdProteinas = Double.parseDouble(scan.nextLine());
						buscas.Busca4(conexao, qtdProteinas);
						break;
					case 5:
						buscas.Busca5(conexao);
						break;
				}
				System.out.println("\nDeseja continuar? \n [y/n]");
				sair = scan.nextLine();

				if(sair.equals("y")) {
					menu = true;
				} else {
					menu = false;
				}
			}

			conexao.close();
			scan.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void inicializapaises(Vector paises) {
		paises.add("United Kingdom");
		paises.add("Canada");
		paises.add("France");
		paises.add("Germany");
		paises.add("Italy");
		paises.add("Romania");
		paises.add("Spain");
		paises.add("Australia");
		paises.add("Belgium");
		paises.add("Netherlands");
		paises.add("United States");
		paises.add("Switzerland");
	}
}
