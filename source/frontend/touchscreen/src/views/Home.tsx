/** @format */

import useGetDrinks from "@/api/endpoints/drinks/getDrinks";
import DrinkSelection from "@/components/DrinkSelection";

function Home(): JSX.Element {
  const { data, isLoading, error } = useGetDrinks;
  if (error) {
    console.log(error);
    return <div>{`:()`}</div>;
  }

  if (isLoading) {
    return <></>;
  }

  return (
    <div>
      <DrinkSelection name="hello" />
    </div>
  );
}

export default Home;
