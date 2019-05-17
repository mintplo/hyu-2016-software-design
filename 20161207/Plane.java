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
        System.out.println("�� ������� �귣��� " + this.brand + " �Դϴ�.");
        System.out.println("�� ������� ���� " + this.model + " �Դϴ�.");
        System.out.println("�� ������� �ִ� ž���ο��� " + this.max_pnum + " �Դϴ�.");
        System.out.println("�� ������� ���� ž���ο��� " + this.pnum + " �Դϴ�.");
        System.out.println("�� ������� �������� " + this.dest + " �Դϴ�.");

        if (this.departureTime != null) {
            System.out.println("�� ������� ��߽ð��� " + this.departureTime.toString() + " �Դϴ�.");
        }
    }
}
