package serialtalk;


public class Leg {
	
		public final LegSlider upper;
		public final LegSlider middle;
		public final LegSlider knee;
		
		public Leg(String idPrefix, Serial serial) {
			upper = new LegSlider(idPrefix+"u", serial);
			middle = new LegSlider(idPrefix+"m", serial);
			knee = new LegSlider(idPrefix+"k", serial);
		}
}
