/** @format */

import ENV from "@/constants/env";

import { useQuery } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./getDrinks.mock.ts");
}

interface GetDrinksResponse {
  drinks: Drink[];
}

export interface Drink {
  id: string;
  name: string;
  remainingFluid: number;
}

const getDrinks = async () => {
  const { data } = await http.get(`v1/drinks`);

  return data as GetDrinksResponse;
};

const useGetDrinks = () => {
  const { data, isLoading, error } = useQuery({
    queryKey: ["getDrinks"],
    queryFn: () => getDrinks(),
  });

  if (error) {
    console.error(error);
  }

  return { data, isLoading, error };
};

export default useGetDrinks;
