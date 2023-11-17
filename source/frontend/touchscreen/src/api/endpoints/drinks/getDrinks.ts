/** @format */

import ENV from "@/constants/env";

import { useQuery } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./getDrinks.mock.ts");
}

export interface Drink {
  id: number;
  image: Image;
  name: string;
  remainingFluid?: number;
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

interface Fluid {
  id: number;
  name: string;
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
