#ifndef Direction_h__
#define Direction_h__

namespace game {

	class Direction {
	public:
		enum e {
			none=0,top=1,bottom=2,vcenter=4,left=8,right=16,hcenter=32,center=4|32,
			topleft=1|8,topright=1|16,bottomleft=2|8,bottomright=2|16,
			centerleft=4|8,centerright=4|16,
			topcenter=1|32,bottomcenter=2|32
		};

		static Direction::e hPart(Direction::e dir) {
			return static_cast<Direction::e>(dir & 0x38);
		}

		static Direction::e vPart(Direction::e dir) {
			return static_cast<Direction::e> (dir & 0x7);
		}

	};

}

#endif // Direction_h__
