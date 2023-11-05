/** @format */

import { useMutation, useQueryClient } from "@tanstack/react-query";

import { http } from "@/api/axios";

interface ChangeContainerRequest {
  id: number; //id of the container
  newFluidId: number; //id of the new fluid
}

export interface ChangeContainerResponse {}

const changeContainer = async ({ id, newFluidId }: ChangeContainerRequest) => {
  const response = await http.patch<ChangeContainerResponse>(
    `v1/containers/${id}`,
    {
      newFluidId,
    }
  );

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useChangeContainer = () => {
  const queryClient = useQueryClient();

  return useMutation({
    mutationKey: ["changeContainer"],
    mutationFn: (request: ChangeContainerRequest) => changeContainer(request),
    onSuccess: () => {
      queryClient.invalidateQueries(["getContainers"]);
    },
  });
};

export default useChangeContainer;
