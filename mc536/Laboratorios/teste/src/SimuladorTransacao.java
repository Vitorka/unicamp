public class SimuladorTransacao {

    private static final int NUMBER_THREADS = 10;

    public static void main(String args[]){

        int i = 0;
        while (i < NUMBER_THREADS){
            Transacao transacao = new Transacao(i+1);
            Thread threadTrans = new Thread(transacao);
            threadTrans.start();
            i++;
        }

    }
}