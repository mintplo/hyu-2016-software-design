import java.text.SimpleDateFormat;
import java.util.*;

public class Plane {
    String brand;
    String model;
    int max_pnum;
    public int pnum;
    String dest;
    public Date departureTime;

    Plane(String brand, String model, int max_pnum, String dest) {
        this.brand = brand;
        this.model = model;
        this.max_pnum = max_pnum;
        this.dest = dest;
    }

    Plane(String brand, String model, int max_pnum, String dest, Date departureTime) {
        this.brand = brand;
        this.model = model;
        this.max_pnum = max_pnum;
        this.dest = dest;
        this.departureTime = departureTime;
    }

    public int getPnum() {
        return pnum;
    }

    public void setPnum(int pnum) {
        this.pnum = pnum;
    }

    public Date getDepartureTime() {
        return departureTime;
    }

    public int register(int value) {
        this.pnum += value;

        return (this.max_pnum - this.pnum);
    }

    public int cancel(int value) {
        this.pnum -= value;

        return (this.max_pnum - this.pnum);
    }

    public int transit(Plane other, int amount) {
        if (other.pnum + amount > other.max_pnum) return -1;
        if (this.pnum < amount) return -1;

        other.register(amount);

        return this.cancel(amount);
    }

    public void print() {
        System.out.println("이 비행기의 브랜드는 " + this.brand + " 입니다.");
        System.out.println("이 비행기의 모델은 " + this.model + " 입니다.");
        System.out.println("이 비행기의 최대 탑승인원은 " + this.max_pnum + " 입니다.");
        System.out.println("이 비행기의 현재 탑승인원은 " + this.pnum + " 입니다.");
        System.out.println("이 비행기의 도착지는 " + this.dest + " 입니다.");

        if (this.departureTime != null) {
            System.out.println("이 비행기의 출발시간은 " + this.departureTime.toString() + " 입니다.");
        }
    }
}
