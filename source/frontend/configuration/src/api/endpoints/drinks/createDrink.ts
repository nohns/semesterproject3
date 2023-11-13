/** @format */

import { Fluid } from "../fluid/getFluids";
import { useMutation, useQueryClient } from "@tanstack/react-query";

import { http } from "@/api/axios";
import { Image } from "../images/getImages";

export interface Ingredient {
  id?: number;
  fluid: Fluid;
  amountInCl: number;
}

export interface CreateDrinkRequest {
  image: Image;
  ingredients: Ingredient[];
  name: string;
}
export interface CreateDrinkResponse {}

const createDrink = async ({
  image,
  name,
  ingredients,
}: CreateDrinkRequest) => {
  const response = await http.post<CreateDrinkResponse>(`v1/drinks`, {
    image,
    name,
    ingredients,
  });

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useCreateDrink = () => {
  const queryClient = useQueryClient();

  return useMutation({
    mutationKey: ["createDrink"],
    mutationFn: (request: CreateDrinkRequest) => createDrink(request),
    onSuccess: (data) => {
      console.log(data);
      queryClient.invalidateQueries(["getDrinks"]);
    },
    onError: (error) => {
      console.log(error);
    },
  });
};

export default useCreateDrink;
