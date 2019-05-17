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
		System.out.println("현재 총 비행기의 대수는 " + Main.numberOfPlanes);
		System.out.println("홍콩행 비행기에 50명 예약 후 남은 좌석 수는 " + plane4.register(50) +"입니다");
		System.out.println("홍콩행 비행기에 30명 취소 후 남은 좌석 수는 " + plane4.cancel(30) +"입니다");
		System.out.println("홍콩행 비행기로 80명 환승 후 " + " 서울행 비행기의  현재 탑승인원은  " + plane3.transit(plane4, 80) +"입니다");
		System.out.println("홍콩행 비행기의 탑승인원은  " + plane4.getPnum() +"입니다");
		plane3.print();
		plane4.print();

		Plane first;
		if (plane3.getDepartureTime().compareTo(plane4.getDepartureTime())< 0)
			first = plane3;
		else
			first = plane4;

		System.out.println("===================");
		System.out.println("먼저 출발할 비행기는 ");
		first.print();
	}

}
