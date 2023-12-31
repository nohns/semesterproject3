/** @format */
import { useMutation, useQueryClient } from "@tanstack/react-query";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/drinks/deleteDrink.mock";

interface DeleteDrinkRequest {
  id: number;
}

export interface DeleteDrinkResponse {}

const deleteDrink = async ({ id }: DeleteDrinkRequest) => {
  const response = await http.delete<DeleteDrinkResponse>(`v1/drinks/${id}`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useDeleteDrink = () => {
  const queryClient = useQueryClient();

  return useMutation({
    mutationKey: ["deleteDrink"],
    mutationFn: (request: DeleteDrinkRequest) => deleteDrink(request),
    onSuccess: () => {
      queryClient.invalidateQueries(["getDrinks"]);
    },
  });
};

export default useDeleteDrink;
