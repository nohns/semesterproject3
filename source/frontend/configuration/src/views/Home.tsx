/** @format */

import useGetContainers from "@/api/endpoints/container/getContainers";
import useGetDrinks from "@/api/endpoints/drinks/getDrinks";
import useGetFluids from "@/api/endpoints/fluid/getFluids";
import useGetImages from "@/api/endpoints/images/getImages";

import MultiStep from "react-multistep";
import Multistepform from "./multistepform/Multistepform";

function Home(): JSX.Element {
  //De her 4 er hooks som der laver API kald
  const images = useGetImages();
  //I kan kalde flere ting på dem de eneste som rigtigt er relevante er isLoading, isError og data
  //Altså om den er igang med at loade dataen stadig, om der er sket en fejl og så selve dataen

  //Nede I JSXen kan I så bruge de forskellige ting ofte bruger man conditional logik altså ternary operators(selvom det er noget pis) og så &&
  //Når man har et array så bruger man en funktion som hedder map til at loope henover dataen så kan man nemlig få flere ting til at render
  //Se neget i JSX'en

  const fluids = useGetFluids();

  const drinks = useGetDrinks();

  const containers = useGetContainers();

  //Her tjekker vi altså for om dataen er loadet ind endnu, hvis den ikke er så viser vi bare en loading besked
  if (
    images.isLoading ||
    fluids.isLoading ||
    drinks.isLoading ||
    containers.isLoading
  ) {
    return <div>Loading...</div>;
  }

  //Hvis i åbner browseren og trykker inspect så kan i åbne developer tooling hvor i kan finde consollen browseren der logger jeg dataen ud
  console.log(images.data?.images);
  console.log(fluids.data?.fluids);
  console.log(drinks.data?.drinks);
  console.log(containers.data?.containers);

  //Her kan i se at jeg bruger .map på data.images som jo er et array så kan vi render 3 billeder slef
  return (
    <>
      <div className="flex flex-col">
        <Multistepform />
        {images.data?.images?.map((image) => (
          <div key={image.id}>
            <img src={image.path} />
          </div>
        ))}
      </div>
    </>
  );
}

export default Home;
