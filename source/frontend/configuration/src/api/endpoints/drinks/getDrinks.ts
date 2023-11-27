/** @format */

import ENV from "@/constants/env";

import { useQuery } from "@tanstack/react-query";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/drinks/getDrinks.mock";

import { Fluid } from "../fluid/getFluids.ts";

export interface Drink {
  id?: number;
  image: Image;
  name: string;
  ingredients: Ingredient[];
}

export interface Ingredient {
  id?: number;
  fluid: Fluid;
  amountInCl: number;
}

interface Image {
  id: number;
  path: string;
}

interface GetDrinksRequest {}
export interface GetDrinksResponse {
  drinks: Drink[];
}

const getDrinks = async ({}: GetDrinksRequest) => {
  const response = await http.get<GetDrinksResponse>(`v1/drinks`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useGetDrinks = () => {
  const query = useQuery({
    queryKey: ["getDrinks"],
    queryFn: () => getDrinks({}),
  });

  return query;
};

export default useGetDrinks;
