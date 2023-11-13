/** @format */

import useGetContainers from "@/api/endpoints/container/getContainers";
import useGetDrinks from "@/api/endpoints/drinks/getDrinks";
import useGetFluids, { Fluid } from "@/api/endpoints/fluid/getFluids";
import useGetImages, { Image } from "@/api/endpoints/images/getImages";

import Header from "@/components/Header";
import Footer from "@/components/Footer";
import ShowFluid from "./fluid/ShowFluid";
import ShowDrink from "./drink/ShowDrink";
import ShowImage from "./image/ShowImage";
import CreateDrinkButton from "./drink/CreateDrinkButton";
import CreateFluidButton from "./fluid/CreateFluidButton";
import useCreateFluid, {
  CreateFluidRequest,
} from "@/api/endpoints/fluid/createFluid";
import useCreateDrink, {
  CreateDrinkRequest,
  Ingredient,
} from "@/api/endpoints/drinks/createDrink";

function Home(): JSX.Element {
  //De her 4 er hooks som der laver API kald
  //const images = useGetImages();
  //I kan kalde flere ting på dem de eneste som rigtigt er relevante er isLoading, isError og data
  //Altså om den er igang med at loade dataen stadig, om der er sket en fejl og så selve dataen

  //Nede I JSXen kan I så bruge de forskellige ting ofte bruger man conditional logik altså ternary operators(selvom det er noget pis) og så &&
  //Når man har et array så bruger man en funktion som hedder map til at loope henover dataen så kan man nemlig få flere ting til at render
  //Se neget i JSX'en

  //const fluids = useGetFluids();

  //const drinks = useGetDrinks();

  //const containers = useGetContainers();

  //Her tjekker vi altså for om dataen er loadet ind endnu, hvis den ikke er så viser vi bare en loading besked
  /*   if (
    images.isLoading ||
    fluids.isLoading ||
    drinks.isLoading ||
    containers.isLoading
  ) {
    return <div>Loading...</div>;
  } */

  /*   //Hvis i åbner browseren og trykker inspect så kan i åbne developer tooling hvor i kan finde consollen browseren der logger jeg dataen ud
  console.log(images.data?.images);
  console.log(fluids.data?.fluids);
  console.log(drinks.data?.drinks);
  console.log(containers.data?.containers); */

  //Mutation functions er til at lave POST, PUT, DELETE requests
  //De fungerer lidt anderledes ved at de først kører når man kalder .mutate på dem hvorimod query funktionerne vil køre lige med det samme

  //Her kan i se at jeg bruger .map på data.images som jo er et array så kan vi render 3 billeder slef
  return (
    <>
      <div className="flex flex-col">
        <Header />
        <div className="text-white text-3xl ">
          <div className="my-4">
            Billeder med containers - Mængde af væske i beholder - Navn af væske
            i beholder{" "}
          </div>
          <div className="my-4">
            Knap til at ændre hvilke drinks man kan vælge
          </div>

          <div className="my-4">
            Vise hvilke drinks man kan vælge imellem og hvilke væsker de består
            af
          </div>
        </div>
      </div>
    </>
  );
}

export default Home;
