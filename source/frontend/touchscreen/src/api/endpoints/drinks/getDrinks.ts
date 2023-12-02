/** @format */

import { useQuery } from "@tanstack/react-query";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/drinks/getDrinks.mock";

export interface Drink {
  id: number;
  image: Image;
  name: string;
  ingredients: Ingredient[];
}

export interface Ingredient {
  id: number;
  fluid: Fluid;
  amountInCl: number;
}

interface Image {
  id: number;
  path: string;
}

export interface Fluid {
  id: number;
  name: string;
}

interface GetDrinksRequest {}
export interface GetDrinksResponse {
  drinks: Drink[];
}

const getDrinks = async ({}: GetDrinksRequest) => {
  console.log("GETTIN DA DRNIKS")
  const response = await http.get<GetDrinksResponse>(`v1/drinks/`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useGetDrinks = () => {
  const query = useQuery({
    queryKey: ["getDrinks"],
    staleTime: 1,
    refetchIntervalInBackground: true,
    refetchInterval: 2000,
    queryFn: () => getDrinks({}),
  });

  return query;
};

export default useGetDrinks;
