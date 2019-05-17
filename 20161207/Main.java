import java.util.Date;

public class Main {

	private static int numberOfPlanes = 0;

	public static void main(String[] args) {
		// TEST2
		Main.numberOfPlanes = 2;

		Plane plane3 = new Plane("Airbus", "A380",500, "Seoul", new Date(2016, 6, 28, 15,30));
		Plane plane4 = new Plane("Boeing","B747", 500, "Hongkong", new Date(2016, 6, 28, 17,0));

		plane3.setPnum(280);
		plane4.setPnum(350);
		System.out.println("���� �� ������� ����� " + Main.numberOfPlanes);
		System.out.println("ȫ���� ����⿡ 50�� ���� �� ���� �¼� ���� " + plane4.register(50) +"�Դϴ�");
		System.out.println("ȫ���� ����⿡ 30�� ��� �� ���� �¼� ���� " + plane4.cancel(30) +"�Դϴ�");
		System.out.println("ȫ���� ������ 80�� ȯ�� �� " + " ������ �������  ���� ž���ο���  " + plane3.transit(plane4, 80) +"�Դϴ�");
		System.out.println("ȫ���� ������� ž���ο���  " + plane4.getPnum() +"�Դϴ�");
		plane3.print();
		plane4.print();

		Plane first;
		if (plane3.getDepartureTime().compareTo(plane4.getDepartureTime())< 0)
			first = plane3;
		else
			first = plane4;

		System.out.println("===================");
		System.out.println("���� ����� ������ ");
		first.print();
	}

}
