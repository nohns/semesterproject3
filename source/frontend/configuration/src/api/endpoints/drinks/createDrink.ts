/** @format */

import { Fluid } from "../fluid/getFluids";
import { useMutation, useQueryClient } from "@tanstack/react-query";

import { http } from "@/api/axios";

interface Ingredient {
  id: number;
  fluid: Fluid;
  amountInCl: number;
}

interface CreateDrinkRequest {
  imageId: number;
  name: string;
  Ingredient: Ingredient[];
}
export interface CreateDrinkResponse {}

const createDrink = async ({
  imageId,
  name,
  Ingredient,
}: CreateDrinkRequest) => {
  const response = await http.post<CreateDrinkResponse>(`v1/drinks`, {
    imageId,
    name,
    Ingredient,
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
    onSuccess: () => {
      queryClient.invalidateQueries(["getDrinks"]);
    },
  });
};

export default useCreateDrink;
