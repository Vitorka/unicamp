import java.sql.*;

public class Transacao implements Runnable {

    private static final String DB_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_CONNECTION = "jdbc:mysql://localhost:3306/folha_unicamp";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "vka-2715-06";

    private int trans_id;

    public Transacao(int i){
        trans_id = i;
    }

    public void run(){
        Connection dbConnection = null;
        PreparedStatement psInsert = null;
        PreparedStatement psSelect = null;
        PreparedStatement psUpdate = null;

        String insertTableSQL = "INSERT INTO folha_unicamp "+
                "(matricula, nome, bruto, indenizacoes, redutor, descontos_legais, liquido, ano, mes) "+
                "VALUES (?,?,?,?,?,?,?,?,?)";

        String selectSQL = "SELECT * FROM folha_unicamp "+
                "WHERE redutor <> 0;";

        String updateTableSQL = "UPDATE folha_unicamp "+
                "SET bruto = 1.10 * bruto "+
                "WHERE ano = 2017 AND mes = 3";

		Savepoint save1 = null;
		Savepoint save2 = null;
		Savepoint save3 = null;

        try {
            dbConnection = getDBConnection();

            // Start Transaction
            long begin = System.currentTimeMillis();
            System.out.println("Starting Transaction "+this.trans_id+" at..."+begin);
            dbConnection.setAutoCommit(false);

            psInsert = dbConnection.prepareStatement(insertTableSQL);
            psInsert.setString(1, "312039");
            psInsert.setString(2, "BRENO BERNARD NICOLAU DE FRAN�A");
            psInsert.setFloat(3, 5000.0f);
            psInsert.setFloat(4, 0.0f);
            psInsert.setFloat(5, 0.0f);
            psInsert.setFloat(6, 1500.0f);
            psInsert.setFloat(7, 3500.0f);
            psInsert.setInt(8, 2019);
            psInsert.setInt(9, this.trans_id);
			save1 = dbConnection.setSavepoint();
            psInsert.executeUpdate();

            psSelect = dbConnection.prepareStatement(selectSQL);

			save2 = dbConnection.setSavepoint();
            ResultSet rs = psSelect.executeQuery();

            psUpdate = dbConnection.prepareStatement(updateTableSQL);
			save3 = dbConnection.setSavepoint();
            psUpdate.executeUpdate();

			dbConnection.commit();
			long end = System.currentTimeMillis();
			System.out.println("End Transaction "+this.trans_id+" at..."+end+". Duration: "+ ((end-begin)/1000));

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            try {
            	if (save1 != null) {
					dbConnection.rollback(save1);
				}
				if (save2 != null) {
					dbConnection.rollback(save2);
				}
				if (save3 != null) {
					dbConnection.rollback(save3);
				}

            } catch (SQLException e1) {
                e1.printStackTrace();
            }
            System.out.println("Transaction "+this.trans_id+" rolled back!");

        } finally {
            try {
				if (psInsert != null) psInsert.close();
				if (psUpdate != null) psUpdate.close();
				if (dbConnection != null) dbConnection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private static Connection getDBConnection() {
        Connection dbConnection = null;
        try {
            Class.forName(DB_DRIVER);
        } catch (ClassNotFoundException e) {
            System.out.println(e.getMessage());
        }
        try {
            dbConnection = DriverManager.getConnection(DB_CONNECTION, DB_USER, DB_PASSWORD);
            return dbConnection;
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return dbConnection;
    }

}
 