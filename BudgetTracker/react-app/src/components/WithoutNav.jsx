import React from 'react';
import { Outlet } from 'react-router';

export const withoutNav = () => {
  return (
    <Outlet />
  )
}

export default withoutNav;