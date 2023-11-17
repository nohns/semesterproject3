/** @format */
import { Drink } from "@/api/endpoints/drinks/getDrinks";
import { Card } from "@/components/ui/card";
import { CardTitle } from "@/components/ui/card";

interface DrinkCardProps {
  drinks: Drink[];
}

function DrinkCard({ drinks }: DrinkCardProps): JSX.Element {
  return (
    <>
      <div className="flex flex-row">
        {drinks.map((drink) => (
          <Card
            key={drink.id}
            className={`flex flex-col w-48 h-48 m-3 rounded-2xl bg-emerald-600  shadow-2xl border-2 transition duration-300 hover:bg-emerald-700 hover:opacity-75
        }`}
            style={{
              backgroundImage: `url("src/assets/HotPot1.png")`,
              backgroundPositionX: "center",
              backgroundPositionY: "bottom",
              backgroundSize: "auto 90%",
              backgroundRepeat: "no-repeat",
              position: "relative", // Add position relative to the card
            }}
          >
            <CardTitle className="font-mono text-black text-center pt-1 font-thin ">
              {drink.name}
            </CardTitle>
          </Card>
        ))}
      </div>
    </>
  );
}

{
  /* <div className="flex flex-row">
{drinks.map((drink) => (
  <div
    className="flex flex-col m-3 rounded-2xl bg-emerald-600 transition duration-300 hover:bg-emerald-700 hover:opacity-75"
    key={drink.id}
  >
    <div className="text-white text-2xl mx-auto">{drink.name}</div>
    <img className="h-40 w-40 mx-auto" src={drink.image?.path} />
  </div>
))}
</div> */
}

export default DrinkCard;
