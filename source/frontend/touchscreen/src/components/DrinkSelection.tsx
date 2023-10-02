/** @format */
import CocktailSvg from "./CocktailSvg";
import { Card, CardTitle } from "./ui/card";

interface DrinkSelectionProps {
  name: string;
}

function DrinkSelection({ name }: DrinkSelectionProps): JSX.Element {
  return (
    <>
      <Card>
        <CardTitle title="hello" />
      </Card>
    </>
  );
}

export default DrinkSelection;
